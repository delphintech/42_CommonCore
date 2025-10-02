import jwt from "jsonwebtoken"

export const newToken = async (res, user) => {
	let exist = false
	if (!user || !user.token) return exist
	jwt.verify(user.token, process.env.JWT_REFRESH_SECRET, (err, user) => {
		if (err) return exist
		const accessToken = jwt.sign({id: user.id}, process.env.JWT_SECRET, { expiresIn: process.env.JWT_EXPIRES })
		res.cookie('accessToken', accessToken, 	{ path: '/', maxAge: parseInt(process.env.JWT_EXPIRES) })
		exist = true
	})
	return exist
}

export const authenticateToken = async (req, res) => {
	const url = req.raw.url;
    if (url.startsWith('/front/') || url.startsWith('/assets/') || url === '/output.css' || url === '/favicon.ico'
		|| url.startsWith('/login') || url.startsWith('/register') || url.startsWith('/token')
		|| url.startsWith('/api/register') || url.startsWith('/api/login') || url.startsWith('/api/dashboard') || url.startsWith('/auth/') || url.startsWith('/metrics'))
    { return }

	let user
	if (req.cookies.id) {
		user = await req.server.models.User.findByPk(req.cookies.id);
	} else { user = null }
	let token = req.cookies.accessToken
	if (!token) {
		if (await !newToken(res, user)) {
			if (url == '/api/user' || url == '/') { return }
			return res.status(401).send()
		} else {
			req.user = user
		}
	} else {
		jwt.verify(token, process.env.JWT_SECRET, async function(err, ok) {
			if (err) {
				if (await !newToken(res, user)) {
					if (url == '/api/user' || url == '/') { return }
					return res.status(401).send()
				} else {
					req.user = user
				}
			} else {
				req.user = user
			}
		})
	}
}
