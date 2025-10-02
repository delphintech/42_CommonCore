
import { where } from "sequelize";
import { Op } from 'sequelize';

/* GET - CREATE TOURNAMENT & REGISTRATION */
export const getCurrentUserData = async (req, res) => {
  	try {
		const user = req.user;
		const userId = user.id;
		let status = 'available';
		let isAdmin = false;
		let tournamentId = null;

		const registration = await req.server.models.Registration.findOne({
            where: { player_id: userId },
            order: [['id', 'DESC']] // Order by ID descending to get the latest
        });

		if (registration) {
			const tournament = await req.server.models.Tournament.findOne({ where: {
				id: registration.tournament_id,
				status: ['hold', 'on']
			}});

			if (tournament) {
				status = 'unavailable';
				tournamentId = tournament.id;
				isAdmin = tournament.admin_id === userId;
			}
		}

		const allFriends = await user.getCurrentFriends();
		const availableFriends = [];
		await Promise.all(allFriends.map(async (friend) => {
			const isRegistered = await req.server.models.Registration.findOne({
				where: { player_id: friend.id },
				include: [{
				model: req.server.models.Tournament,
				where: { status: ['hold', 'on'] },
				required: true
				}]
			});

			if (!isRegistered && friend.online) {
				availableFriends.push(friend);
			}
		}));

		return res.status(200).send({
			status,
			isAdmin,
			tournamentId,
			user,
			availableFriends
		});
	} catch (err) {
		console.error("Error getPlayerStatus:", err);
		return res.status(500).send({ error: 'Server error' });
	}
};

export const getTournamentsAvailable = async (req, res) => {
	const currentUser = req.user;
    if (!currentUser) {
    	return res.status(401).send({ error: 'No currentUser' });
    }

	try {
		const tour = await req.server.models.Tournament.findOne({
			where: {
				admin_id: currentUser.id,
			}
		});

		let ownerOrNot;
		if (tour)
			ownerOrNot = tour.admin_id
		else
			ownerOrNot = currentUser.id

		const {count, rows} = await req.server.models.Tournament.findAndCountAll({
			where: {
				status: 'hold',
				admin_id: {
					[Op.ne]: ownerOrNot,
				}
			}
		});

		return res.status(200).send({
			nb_tournaments: count,
			tournaments: rows,
			user: currentUser
		});

	} catch (err) {
		console.error("ERROR while getting tournaments data", err);
		return res.status(500).send({ error: 'Server error' });
	}
}

export const getShow = async (req, res) => {
    const tournamentId = req.params.id;
    if (!tournamentId)
        return res.status(400).send({ error: 'Missing tournament ID' });

    try {
        const tour = await req.server.models.Tournament.findOne({
            where: { id: tournamentId }
        });

        if (!tour)
            return res.status(404).send({ error: "Tournament not found" });

        const registrations = await req.server.models.Registration.findAll({
            where: { tournament_id: tour.id }
        });

        const playerIds = registrations.map(reg => reg.player_id);

        const players = await req.server.models.User.findAll({
            where: { id: playerIds }
        });

        return res.status(200).send({
            tournament: tour,
            players: players
        });

    } catch (err) {
        console.error('ERROR while getting tournament data and players', err);
        return res.status(500).send({ error: 'Internal server error' });
    }
}

/* POST - CREATE TOURNAMENT & REGISTRATION */

export const createTournament = async (request, reply) => {
	const currentUser = request.user;
    if (!currentUser) {
      return reply.status(401).send({ error: 'No currentUser' });
    }

	try {
		const { name } = request.body;
		if (!name)
			return reply.status(400).send({ error: "Please provide a name to the tournament" });
		if (name.length > 15)
			return reply.status(400).send({ error: "Too long - 15 characters max" });

		const tournament = {
			name: name,
			admin_id: currentUser.id,
			status: 'hold',
			player_number: 1
		}

		const doublon = await request.server.models.Tournament.findOne({ where: {
			name: name
		}});
		if (doublon) {
			return reply.status(400).send({ error: "This tournament name already exists" });
		}

		const newTournament = await request.server.models.Tournament.create(tournament);
		if (!newTournament) {
			return reply.status(400).send({ error: "Error when creating the tournament." });
		}

		const registration = {
			player_id: currentUser.id,
			tournament_id: newTournament.id,
			admin: true,
		}

		const newRegistration = await request.server.models.Registration.create(registration);
		if (!newRegistration) {
			return reply.status(400).send({ error: "Error when creating the registration." });
		}

		currentUser.update({available:false})

		reply.status(201).send({ 
			tournament: newTournament, 
			registration: newRegistration 
		});

	} catch (err) {
		console.error("ERROR while creating a new tournament", err);
		reply.status(500).send({valid: false, message: 'Internal server error'});
	}
}

export const registerPlayer = async (request, reply) => {
	const currentTournamentId = request.params.id;
	const userIdToRegister = request.body.userId;
	if (!currentTournamentId || !userIdToRegister) {
		return reply.status(400).send({ error: 'Missing tournament ID or user ID' });
	}

	try {
		const tournament = await request.server.models.Tournament.findByPk(currentTournamentId);
		if (!tournament) {
			return reply.status(404).send({ error: 'Tournament not found' });
		}

		const existingRegistration = await request.server.models.Registration.findOne({
			where: {
				tournament_id: currentTournamentId,
				player_id: userIdToRegister
			}
		});
		if (existingRegistration) {
			return reply.status(400).send({ error: "Already registered in another tournament" });
		}

		const anotherExistingRegistration = await request.server.models.Registration.findOne({ where: {
			player_id: userIdToRegister
		}});
		if (anotherExistingRegistration) {
			const anotherTournament = await request.server.models.Tournament.findOne({where: {
				status: ['hold', 'on'],
				id: anotherExistingRegistration.tournament_id
			}});

			if (anotherTournament) {
				return reply.status(400).send({ error: "Already registered in another tournament" });
			}
		}

		if (tournament.player_number >= 4) {
			return reply.status(400).send({ error: "Tournament is full" });
		}

		const registration = await request.server.models.Registration.create({
			player_id: userIdToRegister,
			tournament_id: currentTournamentId,
			admin: false,
		});
		if (!registration) {
			return reply.status(400).send({ error: "Error when creating the registration." });
		}

		await request.server.models.User.update(
			{ available: false },
			{ where: { id: userIdToRegister } }
		);

		const nb_registrations = await request.server.models.Registration.count({ where: {
			tournament_id: currentTournamentId,
		}});

		tournament.player_number = nb_registrations;
		await tournament.save();

		reply.status(201).send({ registration, tournament });

	} catch (err) {
		console.error('Error registering player and updating tournament', err);
		reply.status(500).send({ error: 'Server error' });
	}
};

export const startTournament = async (request, reply) => {
    const tournamentId = request.params.id;

    try {
        const tournament = await request.server.models.Tournament.findByPk(tournamentId);
        if (!tournament) {
            return reply.status(404).send({ error: 'Tournament not found' });
        }

        const currentUser = request.user;
        if (tournament.admin_id !== currentUser.id) {
            return reply.status(403).send({ error: 'Not authorized to start this tournament' });
        }

        if (tournament.status === 'on') {
            return reply.status(400).send({ error: 'Tournament already started' });
        }

        tournament.status = 'on';
        await tournament.save();

		if (tournament.combinations) {
            try {
                const combinations = JSON.parse(tournament.combinations);
                
                if (combinations && combinations.combinations && Array.isArray(combinations.combinations)) {
                    // Get the first match (contains 2 games)
                    const firstMatch = combinations.combinations[0];
                    
                    if (Array.isArray(firstMatch) && firstMatch.length >= 2) {
                        const firstTwoGameIds = [firstMatch[0].id, firstMatch[1].id];
                        
                        // Update the first 2 games to status 'hold'
                        await request.server.models.Game.update(
                            { status: 'hold' },
                            { 
                                where: { 
                                    id: firstTwoGameIds,
                                    tournament_id: tournamentId 
                                } 
                            }
                        );
                    }
                }
            } catch (err) {
                console.error('Error parsing combinations or updating games:', err);
            }
        }

        return reply.status(200).send({ success: true, tournament });

    } catch (err) {
        console.error('Error starting tournament', err);
        reply.status(500).send({ error: 'Server error' });
    }
};


/* DELETE - QUIT & DELETE TOURNAMENT */
export const quitTournament = async (request, reply) => {
	const currentTournamentId = request.params.id;
	const userIdToRegister = request.body.userId;
	if (!currentTournamentId || !userIdToRegister) {
		return reply.status(400).send({ error: 'Missing tournament ID or user ID' });
	}

	try {
		const tournament = await request.server.models.Tournament.findByPk(currentTournamentId);
		if (!tournament) {
		return reply.status(404).send({ error: 'Tournament not found' });
		}

		await request.server.models.Registration.destroy({ where: {
			player_id: userIdToRegister,
			tournament_id: currentTournamentId,
			admin: false,
		}});

		const nb_registrations = await request.server.models.Registration.count({ where: {
			tournament_id: currentTournamentId,
		}});

		tournament.player_number = nb_registrations;
		if (tournament.player_number < 4)
			tournament.status = 'hold';

		await tournament.save();

		reply.status(200).send({ tournament });

	} catch (err) {
		console.error('Error unregistering player and updating tournament', err);
		reply.status(500).send({ error: 'Server error' });
	}
}

export const deleteTournament = async (req, res) => {
	try {
		const tour_id = req.params.id;

		const registrations = await req.server.models.Registration.findAll({
            where: { tournament_id: tour_id }
        });

        const playerIds = registrations.map(reg => reg.player_id);

		await req.server.models.User.update(
			{ available: true },
			{ where: { id: playerIds } }
		);

		await req.server.models.Game.destroy({ where: { tournament_id: tour_id }});

		await req.server.models.Registration.destroy({ where: { tournament_id: tour_id }});
			
		const tour = await req.server.models.Tournament.destroy({ where: { 
			id: tour_id 
		}});
		if (!tour)
			return res.status(404).send({ error: "Tournament not found" });

		return res.status(200).send({message: "Tournament deleted"});
	} catch (err) {
		console.error("ERROR while deleting the tournament", err);
		return res.status(500).send({ error: 'Server error' });
	}
}

export const createPairs = async (request, reply) => {
	try {
		const content = request.body.data.content;
		const tournamentId = request.body.data.tournamentId;

		if (!content) {
			return reply.status(400).send({ error: 'No content data provided' });
		}
		if (!tournamentId) {
			return reply.status(400).send({ error: 'No tournamentId provided' });
		}

		const tournament = await request.server.models.Tournament.findByPk(tournamentId);
		if (!tournament) {
			return reply.status(404).send({ error: 'Tournament not found' });
		}

		tournament.set({combinations: JSON.stringify(content)});
		tournament.save()

		reply.status(201).send({message: "Pairs created"});
	} catch (err) {
		console.error('Error writing file:', err);
		return reply.status(500).send({ error: 'Failed to save content' });
	}
};


export const getNextGameTour = async (request, reply) => {
    
    try {
        const tournamentId = request.params.id;
        const currentUser = request.user;
        if (!currentUser) {
            return reply.status(401).send({ error: 'No currentUser' });
        }
        const tournament = await request.server.models.Tournament.findByPk(tournamentId);
        if (!tournament) {
            return reply.status(404).send({ error: 'Tournament not found' });
        }

        const nextGames = await currentUser.getGames({ where: { 
            tournament_id: tournament.id,
            status: ['hold', 'waiting_tournament']
        }})

		if (nextGames.length == 0) {
			return reply.status(204).send({ 
				nb_next_games: 0,
			});
		}

        let combinations = null;
        let orderedGameIds = [];
        if (tournament.combinations) {
            try {
                combinations = JSON.parse(tournament.combinations);
                
                // Extract all game IDs in order
                if (combinations && combinations.combinations && Array.isArray(combinations.combinations)) {
                    combinations.combinations.forEach(match => {
                        if (Array.isArray(match)) {
                            match.forEach(game => {
                                if (game && game.id) {
                                    orderedGameIds.push(game.id);
                                }
                            });
                        }
                    });
                }
            } catch (err) {
                console.error('Error parsing combinations:', err);
            }
        }

        // Filter orderedGameIds to only include IDs that exist in nextGames
        const nextGameIds = nextGames.map(game => game.id);
        const filteredOrderedGameIds = orderedGameIds.filter(id => nextGameIds.includes(id));

		const orderedGames = await request.server.models.Game.findAll({
            where: {
                id: filteredOrderedGameIds
            },
            order: [
                // Order by the position in filteredOrderedGameIds
                request.server.models.Game.sequelize.literal(
                    `CASE ${filteredOrderedGameIds.map((id, index) => `WHEN id = ${id} THEN ${index}`).join(' ')} END`
                )
            ]
        });

		const next_game = orderedGames[0]

        return reply.status(200).send({ 
            nb_next_games: nextGames.length,
			next_game: next_game
        });
    } catch (err) {
        console.error('Error starting tournament', err);
        reply.status(500).send({ error: 'Server error' });
    }
};


export const updateFinishedTournament = async (request, reply) => {
    const tournamentId = request.params.id;

    try {
        const tournament = await request.server.models.Tournament.findByPk(tournamentId);
        if (!tournament) {
            return reply.status(404).send({ error: 'Tournament not found' });
        }

        const currentUser = request.user;
        if (tournament.admin_id !== currentUser.id) {
            return reply.status(403).send({ error: 'Not authorized to start this tournament' });
        }

        const {count, rows: games} = await request.server.models.Game.findAndCountAll({ where : {
            tournament_id: tournament.id,
            status: 'done'
        }});
        if (count != 6) {
            return reply.status(400).send({ error: 'The tournament is not done.' });
        }

        // Calculate player scores
        const playerScores = {};
        
        // Get all players in the tournament - using separate queries approach
        const registrations = await request.server.models.Registration.findAll({
            where: { tournament_id: tournament.id }
        });

        const playerIds = registrations.map(reg => reg.player_id);

        const players = await request.server.models.User.findAll({
            where: { id: playerIds },
        });

        // Initialize player scores
        for (const player of players) {
            playerScores[player.id] = {
                id: player.id,
                username: player.username,
                totalPoints: 0,
                gamesWon: 0,
                gamesPlayed: 0
            };
        }

		await request.server.models.User.update(
			{ available: true },
			{ where: { id: playerIds } }
		);

        // Calculate scores from all games
        for (const game of games) {
            // Get the plays for this game to access the scores
            const plays = await request.server.models.Play.findAll({
                where: { game_id: game.id },
                include: [{
                    model: request.server.models.User,
                    as: 'opp',
                    attributes: ['id', 'username']
                }]
            });
            
            // Process each play (should be 2 plays per game)
            for (const play of plays) {
                const playerId = play.player_id;
                
                if (playerScores[playerId]) {
                    // Add the score from this play
                    playerScores[playerId].totalPoints += play.score || 0;
                    playerScores[playerId].gamesPlayed++;
                    
                    // Check if this player won the game
                    if (game.winner_id === playerId) {
                        playerScores[playerId].gamesWon++;
                    }
                }
            }
        }

        // Convert to array and sort by total points (descending)
        const sortedPlayers = Object.values(playerScores).sort((a, b) => {
            // First sort by games won
            if (b.gamesWon !== a.gamesWon) {
                return b.gamesWon - a.gamesWon;
            }
            //  If tied on games won, sort by total points
            if (b.totalPoints !== a.totalPoints) {
                return b.totalPoints - a.totalPoints;
            }
            // If still tied, sort by username for consistency
            return a.username.localeCompare(b.username);
        });

        // Determine winner and podium
        const winner = sortedPlayers[0];
        const podium = sortedPlayers.slice(0, 3); // Top 3 players

        // Update tournament with winner info
        tournament.status = 'done';
        tournament.winner_id = winner.id;
        await tournament.save();
		const message = 'The winner of the tournament ' + tournament.name + ' is 🎉 ' + winner.username + ' 🎉';

		// The winner is 🎉 ${actualGame.guest} 🎉
        return reply.status(200).send({ 
            success: true, 
            tournament,
            winner: winner,
            podium: podium,
            allPlayerScores: sortedPlayers,
			message: message
        });

    } catch (err) {
        console.error('Error finishing tournament', err);
        reply.status(500).send({ error: 'Server error' });
    }
};