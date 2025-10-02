export const getUserFriends = async (req, res) => {
	if (!req.user) {
		return res.status(401).send({ error: 'No currentUser' });
	}
    try {
		const currents = await req.user.getCurrentFriends();
		const pendings = await req.user.getPendingFriends();
		return res.status(200).send({
			currents: currents.map(c => c.get({ plain: true })),
			pendings: pendings.map(p => p.get({ plain: true }))
		});
    } catch (err) {
        console.error("ERROR while getting all user's friends", err);
        return res.status(500).send({});
    }
}

export const getUserFriend = async (req, res, next) => {
	try {
      const friend = await req.user.getFriend(req.params.id)
		if (!friend)
			return res.status(404).send({ error: "You are not friend with this user" });
		return res.status(200).send({
			friend: friend.get({ plain: true })
		});
    } catch (err) {
        console.error("ERROR while getting 1 friend user's data", err);
        return res.status(500).send({});
    }
}

export const createNewFriendship = async (req, res) => {
	const friendName = req.body.friend_username.value
	if (friendName == req.user.username) {
		return res.status(400).send({ error: "Asking yourself as friend is not allowed ... and sad !" });
	}
	const friend = await req.server.models.User.findOne({ where: { username: friendName } });
	if (!friend)
		return res.status(404).send({ error: `the user ${friendName} does not exists` });
	let friendship = await req.user.getFriendship(friend.id)

	if (friendship) {
		if (friendship.approved) {
			return res.status(403).send({ error: `You are already friend with ${friendName}` });
		} else {
			return res.status(403).send({ error: `A request has already been sent to ${friendName}` });
		}
	}

	try {
		friendship = await req.server.models.Friend.create({
			user_id: req.user.id,
			friend_id: friend.id
		})
		return res.status(200).send({
			friendship: friendship.get({ plain: true }),
			asker: req.user.get({ plain: true }),
			replier: friend.get({ plain: true })
		})
	} catch (error) {
		return res.status(500).send(error);
	}
}

// Get all the pending friend requests sent to the current user
export const getFriendRequests = async (req, res) => {
	try {
		const friendships = await req.server.models.Friend.findAll({  where: {
			friend_id: req.user.id,
			approved: false
		}})

		const requests = []
		for (const friendship of friendships) {
			const asker = await req.server.models.User.findByPk(friendship.user_id)
			requests.push({
				friendship: friendship.get({plain: true}),
				asker: asker.get({ plain: true }),
				replier: req.user.get({ plain: true })
			})
		}
		return res.status(200).send({pendings: requests})
	} catch (error) {
		return res.status(500).send(error);
	}
}

export const updateFriendship = async (req, res) => {
	const data = req.body
	try {
		const friendship = await req.server.models.Friend.findOne( { where: {
			user_id: data.friend_id,
			friend_id: req.user.id
		}})
		if (data.approved) {
			await friendship.update({approved: true})
		} else {
			await friendship.destroy()
		}
		return res.status(200).send( {
			approved: data.approved,
			replier: req.user.get({ plain: true }),
			asker_id: data.friend_id
		})
	} catch (error) {
		return res.status(500).send(error);
	}
}

export const deleteFriend = async (req, res, next) => {
	try {
		const friendship = await req.user.getFriendship(req.params.id)
		if (!friendship) {
			return res.status(404).send({ error: "This friendship does not exist"})
		}
		let victim_id
		if (req.user.id == friendship.user_id) {
			victim_id = friendship.friend_id
		} else {
			victim_id = friendship.user_id
		}
		await friendship.destroy()
		return res.status(200).send({
			deleter: req.user.get({ plain: true }),
			victim_id: victim_id })
	} catch (err) {
		return res.status(500).send({err});
	}
}
