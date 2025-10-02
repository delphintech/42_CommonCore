import type { Config } from 'tailwindcss'

const config: Config = {
	content: [
		"./src/**/*.{ejs,html,ts,js}",
	],
	theme: {
		extend: {
			colors: {
				"wall": "#D9D9D9",
				"arcade": {
					'clair': "#F8CC4D",
					'obscur': "#F8BC4D"
				},
				'plank': "#9C9C9C",
				"wood": "#613114",
				'cork': "#B07734",
				'cork_light': "#D19B5C",
				"screen": "#151515",
				"around_screen": "#414141",
				"button_player": {
					'clair': "#D9D9D9",
					'obscur': "#BEBEBE"
				},
				"button_green": "#2BE417",
				"button_red": '#B91C1C',
			},
			fontFamily: {
				principal: ['Kodchasan', 'sans-serif'],
				on_paper: ['Caveat'],
				score: ['"Micro 5"'],
				players: ['"Press Start 2P"']
			},
			width: {
        		'game-screen-ratio-w': 'calc(100% * 690 / 1440)', // 690:1440 width-to-height
				'player-name-ration-w': 'calc(100% * 400 / 1440)',
				'div-plate-w': 'calc(100% * 1100 / 1440)'
      		},
			height: {
				'game-screen-ratio-h': 'calc(100% * 450 / 1024)',
				'player-name-ration-h': 'calc(100% * 25 / 1024)',
				'div-plate-h': 'calc(100% * 250 / 1024)'
			},
			backgroundImage: {
				'paper': "url('/assets/paper.webp')",
			},
			padding: {
      			'ratio': '4%',
				'test': '15%',
			}
		}
	},
	plugins: [],
}
module.exports = config;