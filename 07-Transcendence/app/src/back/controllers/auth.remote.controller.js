import jwt from "jsonwebtoken"

const window = (type, message) => {		
	return `<!DOCTYPE html>
		<html>
			<body>
				<script>
					window.opener.postMessage({
						type: "${type}",
						message: "${message}"
					}, window.origin);
					window.close();
				</script>
			</body>
		</html>`
}

const signIn = async (user, req, res) => {
	// Check if user already exists
	let current = await req.server.models.User.findOne({where: {username: user.username}})
	if (!current) {
		current = await req.server.models.User.findOne({where: {username: user.email}})
	}
	// If user exists
	if (current) {
		if (user.auth != current.auth) {
			return res.status(409).header('Content-Type', 'text/html').send(
				window('auth-error', `${user.username} already exists but uses ${current.auth} as authentication method.`)
			);
		}
	} else { // Create if it does not exists
		const avatar = await req.server.imageUpload(user.avatar)
		current = await req.server.models.User.create({
			username: user.username,
			email: user.email,
			auth: user.auth,
			avatar: avatar,
		});
	}
	try {
		if (user.online) {
				window('auth-error', `You are already logged in somewhere !`)
		} else if (current.tfa) {
			res.cookie('id', current.id, { path: '/'})
			return res.status(200).header('Content-Type', 'text/html').send(
				window('auth-tfa', `Two-factor authentification !`)
			);
		} else {
			// Create session token
			const accessToken = jwt.sign({id: current.id}, process.env.JWT_SECRET, { expiresIn: process.env.JWT_EXPIRES })
			const refreshToken = jwt.sign({id: current.id}, process.env.JWT_REFRESH_SECRET, { expiresIn: '1d' })
			current.token = refreshToken
			current.online = true
			await current.save()
			res.cookie('accessToken', accessToken, 	{ path: '/', maxAge: parseInt(process.env.JWT_EXPIRES) })
			res.cookie('id', current.id, { path: '/'})
			return res.status(200).header('Content-Type', 'text/html').send(
				window('auth-success', `Welcome ${current.username} !`)
			);
		}
	} catch (error) {
		return res.status(500).header('Content-Type', 'text/html').send(
			window('auth-error', `Oops! Something went wrong. PLease try again`)
		);
	}
}

/********** GOOGLE **********/
export const google = async (_req, res) => {
	const redirUrl = `${process.env.HOST}/auth/google/callback`
	const url = `https://accounts.google.com/o/oauth2/v2/auth?client_id=${process.env.GOOGLE_CLIENT_ID}&redirect_uri=${redirUrl}&response_type=code&scope=email profile&access_type=offline&prompt=consent`;

	res.redirect(url)
}

export const googleCallback = async (req, res) => {
	const params = new URLSearchParams({
			client_id: process.env.GOOGLE_CLIENT_ID,
			client_secret: process.env.GOOGLE_CLIENT_SECRET,
			code: req.query.code,
			redirect_uri: `${process.env.HOST}/auth/google/callback`,
			grant_type: 'authorization_code',
	})
	const response = await fetch("https://oauth2.googleapis.com/token", {
		method: "POST",
		headers: {
			"Content-Type": "application/x-www-form-urlencoded"
		},
		body: params.toString(),
	})
	if (!response.ok) {
		return res.status(500).header('Content-Type', 'text/html').send(
			window('auth-error', `Oops! Something went wrong. PLease try again`)
		)
	}
	const data = await response.json()
	// Get profile
	const profileRes = await fetch("https://www.googleapis.com/oauth2/v2/userinfo", {
		method: "GET",
		headers: {
			Authorization: `Bearer ${data.access_token}`,
			Accept: "application/json"
		},
	});
	
	if (!profileRes.ok) {
		return res.status(500).header('Content-Type', 'text/html').send(
			window('auth-error', `Oops! Something went wrong. PLease try again`)
		)
	}
	const profile = await profileRes.json()

	const user = {
		username: profile.name,
		email: profile.email,
		auth: "google",
		avatar: profile.picture
	}
	return signIn(user, req, res)
}

/********** GITHUB **********/
export const github = async (_req, res) => {
	const redirUrl = `${process.env.HOST}/auth/github/callback`
	const url = `https://github.com/login/oauth/authorize?client_id=${process.env.GITHUB_CLIENT_ID}&redirect_uri=${redirUrl}&scope=user%20user:email&prompt=consent`;

	res.redirect(url)
}

export const githubCallback = async (req, res) => {
	const params = new URLSearchParams({
		client_id: process.env.GITHUB_CLIENT_ID,
		client_secret: process.env.GITHUB_CLIENT_SECRET,
		code: req.query.code
	})
	const response = await fetch(`https://github.com/login/oauth/access_token?${params}`, {
		headers: {
			Accept: "application/json",
		},
	})
	if (!response.ok) {
		return res.status(500).header('Content-Type', 'text/html').send(
			window('auth-error', `Oops! Something went wrong. PLease try again`)
		)
	}
	const data = await response.json()

	// Get profile
	const profileRes = await fetch("https://api.github.com/user", {
		method: "GET",
		headers: {
			Accept: "application/json",
			Authorization: `bearer ${data.access_token}`
		},
	});
	// Get mail
	const mailRes = await fetch("https://api.github.com/user/emails", {
		method: "GET",
		headers: {
			Accept: "application/json",
			Authorization: `bearer ${data.access_token}`
		},
	});
	if (!profileRes.ok || !mailRes.ok) {
		return res.status(500).header('Content-Type', 'text/html').send(
			window('auth-error', `Oops! Something went wrong. PLease try again`)
		)
	}
	const profile = await profileRes.json()
	const emails = await mailRes.json()
	const email = emails.find(email => email.primary && email.verified);

	const user = {
		username: profile.login,
		email: email.email,
		auth: "github",
		avatar: profile.avatar_url
	}
	return signIn(user, req, res)
}