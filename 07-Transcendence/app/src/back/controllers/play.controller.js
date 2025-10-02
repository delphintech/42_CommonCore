import { Op } from 'sequelize';

export async function getUserPlay(request, reply) {

  const currentUser = request.user;
  if (!currentUser) {
    return reply.status(400).send({ error: 'No currentUser' });
  }

  try {
    const play = await req.server.models.Play.findOne({
			where: {
				id: req.params.id,
			}
		});
    return reply.send({ play: play });
  } catch (err) {
    request.server.log.error(err);
    reply.status(500).send({ error: 'Erreur serveur' });
  }
}

export async function getUserActualPlay(request, reply) {
  const currentUser = request.user;
  if (!currentUser) {
    return reply.status(401).send({ error: 'No currentUser' });
  }

  try {
    const currentUserPlay = await request.server.models.Play.findOne({
      where: {
        player_id: currentUser.id,
      },
      include: [{
        model: request.server.models.Game,
        as: 'Game',
        where: {
          status: ['hold', 'on'] 
        }
      }]
    });
    if (!currentUserPlay) {
      return reply.status(204).send({ error: 'No play' });
    }

    const game = await request.server.models.Game.findOne({ where: { id: currentUserPlay.game_id } });
    if (!game) {
      return reply.status(404).send({ error: 'Game not found' });
    }

    const play = await request.server.models.Play.findOne({
      where: {
        id: { [Op.ne]: currentUserPlay.id },
        game_id: game.id
      }
    });
    if (!play) {
      return reply.status(404).send({ error: 'Other Play not Found' });
    }

    const otherPlayer = await request.server.models.User.findOne({ where: { id: play.player_id } });
    if (!otherPlayer)
      return res.status(404).send({ error: "other user not found" });

    return reply.status(200).send({
      nb_plays: 1,
      currentPlay: currentUserPlay,
      currentPlayer: currentUser,
      currentSide: currentUserPlay.side,
      game: game,
      otherPlay: play,
      otherPlayer: otherPlayer
    });

  } catch (err) {
    request.server.log.error(err);
    reply.status(500).send({ error: 'Erreur serveur' });
  }
}

export async function getGamePlay(request, reply) {

  const currentUser = request.user;
  if (!currentUser) {
    return reply.status(400).send({ error: 'No currentUser' });
  }

  try {
    const plays = await request.server.models.Play.findAll({
      where: {
        player_id: currentUser.id,
      },
      include: [{
        model: request.server.models.Game,
        as: 'Game',
        where: {
          status: { [Op.ne]: 'done' }
        }
      }]
    });
    return reply.status(200).send({ play: plays });
  } catch (err) {
    request.server.log.error(err);
    reply.status(500).send({ error: 'Erreur serveur' });
  }
}

export async function acceptChallenge(request, reply) {
  const currentUser = request.user;
  if (!currentUser) {
    return reply.status(400).send({ error: 'No currentUser' });
  }
  const game_Id = request.params.id;
  try {
    const play = await request.server.models.Play.findOne({
			where: {
				player_id: currentUser.id,
        game_id: game_Id
			}
		});
    if (!play) {
      return reply.status(404).send({ error: 'Play not found' });
    }
    play.set({accepted: true});
    currentUser.set({available: false});

    await play.save();
    await currentUser.save();

    return reply.status(200).send({ valid: true });
  } catch (err) {
    request.server.log.error(err);
    reply.status(500).send({ error: 'Erreur serveur' });
  }
}

export async function readyPlay(request, reply) {
  try {
    const ready = request.body.ready;

    const play = await request.server.models.Play.findOne({
			where: {
				id: request.params.id,
			}
		});
    if (!play) {
      return reply.status(404).send({ error: 'Play not found' });
    }
    play.set({ready_play: ready});

    await play.save();

    return reply.status(200).send({ valid: true });
  } catch (err) {
    request.server.log.error(err);
    reply.status(500).send({ error: 'Erreur serveur' });
  }
}

export async function getUserStats(request, reply) {
  const currentUser = request.user;
  if (!currentUser) {
    return reply.status(401).send({ error: 'No currentUser' });
  }

  try {
    const plays = await request.server.models.Play.findAll({
      where: { player_id: currentUser.id }
    });

    const playCount = plays.length;
    const winCount = plays.filter(p => p.win === true).length;
    const lostCount = plays.filter(p => p.win === false).length;
    const scores = plays.map(p => p.score);
    const winLooseRatio = plays.map(p => p.win);

    return reply.send({
      plays,
      playCount,
      winCount,
      lostCount,
      scores,
      winLooseRatio
    });
  } catch (err) {
    request.server.log.error(err);
    return reply.status(500).send({ error: 'Erreur serveur' });
  }
}

export async function getUserOpponents(request, reply) {
  const currentUser = request.user;
  if (!currentUser) {
    return reply.status(401).send({ error: 'No currentUser' });
  }

  try {

    const userPlays = await request.server.models.Play.findAll({
      where: { player_id: currentUser.id },
      attributes: ['game_id'],
      raw: true,
    });
    const gameIds = userPlays.map(p => p.game_id);
    if (gameIds.length === 0) return reply.send({ opponents: [] });

    const opponents = await  request.server.models.Play.findAll({
      where: {
        game_id: { [Op.in]: gameIds },
        player_id: { [Op.ne]: currentUser.id },
      },
      include: [
        {
          model: request.server.models.User,
          as: 'opp',
          attributes: ['id', 'username']
        }
      ],
      attributes: ['game_id'],
      raw: true,
      nest: true
    });

    const formatted = opponents.map(p => ({
      game_id: p.game_id,
      opponent_id: p.opp.id,
      opponent_username: p.opp.username
    }));

    return reply.send({ opponents: formatted });

  } catch (err) {
    request.server.log.error(err);
    return reply.status(500).send({ error: 'Erreur serveur iii' });
  }
}
