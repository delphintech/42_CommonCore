import bcrypt from "bcrypt"

export const user = (req, res) => {
	if (!req.user) {
		return res.status(204).send({})
	}
  req.user.update({ online: true });
	const options = req.cloud_options || {}
	options.folder = 'avatars'
	const url = req.server.cloudinary.url(req.user.avatar, options)
	return res.status(200).send({user: req.user.get({plain: true}), avatar: url})
}

export const getUser = async (req, res) => {
	try {
		const id = req.params.id;
		const user = await req.server.models.User.findByPk(id);
		if (!user)
			return res.status(404).send({ error: "User from id not found", id: id });

		return res.status(200).send(user.get({ plain: true }));

	} catch (err) {
		console.error('ERROR while getting tournament data from id', err);
		return res.status(500).send({});
	}
}

export const toggleTFA = async (req, res) => {
	const currentUser = req.user;
	if (!currentUser) {
		return res.status(401).send({ error: 'No currentUser' });
	}
	const tfa = currentUser.tfa
	try {
		await currentUser.update({ tfa: !tfa, totp: null })
		return res.status(200).send({ valid: true })
	} catch (err) {
		console.log(err);
		return res.status(500).send({ error: 'Erreur serveur' });
	}
}

// do not delete anything below

export async function getFullUserProfile(request, reply) {

  const user = request.user;

    if (!user) {
      return reply.status(401).send({ error: 'Utilisateur non authentifié' });
    }

    try {
      const options = request.cloud_options || {};
      options.folder = 'avatars';
      const avatarUrl = request.server.cloudinary.url(user.avatar, options);

      const friends = await user.getCurrentFriends();

      const userProfile = {
        id: user.id,
        username: user.username,
        email: user.email,
        avatar: avatarUrl,
        friends: friends,
        friendsCount: friends.length,
		tfa: user.tfa
      };

      reply.send(userProfile);

    } catch (err) {
      request.server.log.error(err);
      reply.status(500).send({ error: 'Erreur serveur' });
    }
}

export async function updateUserProfile(request, reply) {

  const userSession = request.user;

    if (!userSession) {
      return reply.status(401).send({ error: 'Utilisateur non authentifié' });
    }

    const { username, email, password } = request.body;

    if (
      (!username || username.trim() === '') &&
      (!email || email.trim() === '') &&
      (!password || password.trim() === '')
    ) {
      return reply.status(400).send({ error: 'Aucune donnée valide à mettre à jour' });
    }

    try {
      const userModel = await request.server.models.User.findByPk(userSession.id);

      if (!userModel) {
        return reply.status(404).send({ error: 'Utilisateur non trouvé' });
      }

      if (username) {
        if (username.trim() === '') {
          return reply.status(400).send({ error: 'Nom d’utilisateur invalide' });
        }
        userModel.username = username;
      }

      if (email) {
        if (email.trim() === '') {
          return reply.status(400).send({ error: 'Email invalide' });
        }
        userModel.email = email;
      }

      if (password) {
        if (password.trim() === '') {
          return reply.status(400).send({ error: 'Mot de passe invalide' });
        }
        const salt = await bcrypt.genSalt();
        const hashedPwd = await bcrypt.hash(password, salt);
        userModel.password = hashedPwd;
      }

      await userModel.save();

      reply.send({
        id: userModel.id,
        username: userModel.username,
        email: userModel.email,
      });

    } catch (err) {
      request.server.log.error(err);
      reply.status(500).send({ error: 'Erreur serveur' });
    }
}

export async function uploadAvatar(request, reply) {
  const currentUser = request.user;
  if (!currentUser) {
    return reply.status(401).send({ error: 'No currentUser' });
  }

  try {
    const newAvatar = await request.body.avatar;

    if (!newAvatar.file.bytesRead) {
      return reply.status(400).send({ error: 'Aucun fichier envoyé' });
    }
	  const public_id = await request.server.imageUpload(newAvatar)

    // Met à jour l'utilisateur avec le public_id ou l'URL
    await currentUser.update({ avatar: public_id });

    const url = request.server.cloudinary.url(public_id, {
      folder: 'avatars',
      ...request.cloud_options, // Copie toutes les propriétés de obj dans un nouvel objet pour plus de fluidité coté front
    });
    reply.status(200).send({ avatar: url });


  } catch (err) {
    request.server.log.error(err);
    reply.status(500).send({ error: 'Erreur serveur' });
  }
}
