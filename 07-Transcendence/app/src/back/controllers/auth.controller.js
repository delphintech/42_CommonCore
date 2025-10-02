import bcrypt from "bcrypt"
import jwt from "jsonwebtoken"

export const login = async (req, res) => {
	const user = await req.server.models.User.findOne({where: { username: req.body.username }});
	if (user == null)
		return res.status(400).send({ error: 'Unauthorized' });
	try {
		if (await bcrypt.compare(req.body.password, user.password)) {
			// if (user.online) {
			// 	return res.status(401).send({error: 'You are already logged in !'});
			if (user.tfa) {
				res.cookie('id', user.id, { path: '/'})
				return res.status(200).send({valid: true, message: 'Waiting two-factors auth !', user: user, tfa: true});
			} else {
				const accessToken = jwt.sign({id: user.id}, process.env.JWT_SECRET, { expiresIn: process.env.JWT_EXPIRES })
				const refreshToken = jwt.sign({id: user.id}, process.env.JWT_REFRESH_SECRET, { expiresIn: '1d' })
				await user.update({ token: refreshToken, online: true })
				res.cookie('accessToken', accessToken, 	{ path: '/', maxAge: parseInt(process.env.JWT_EXPIRES) })
				res.cookie('id', user.id, { path: '/'})
				return res.status(200).send({valid: true, message: 'Logged in !', user: user, tfa: false});
			}
		} else {
			return res.status(401).send({error: 'Forbidden'});
		}
	} catch (err) {
		console.log(err)
		return res.status(500).send({error: 'Internal server error'});
	}
}

export const register = async (req, res) => {
    let data = req.body;
	if (data.username.length < 4 || data.username.value.length > 15) {
		return res.status(406).send({valid: false, message: "The username must be between 4 and 16 characters."});
	}
	if (await req.server.models.User.findOne({where: {username: data.username.value}})) {
		return res.status(409).send({valid: false, message: "Username already used, please choose another one."});
	}
	// Check mail
	if (await req.server.models.User.findOne({where: {email: data.email.value}})) {
		return res.status(409).send({valid: false, message: "There is already an account with that email."});
	}
	if (!data.email.value.match(/\b[\w\.-]+@[\w\.-]+\.\w{2,4}\b/gi)) {
		return res.status(400).send({valid: false, message: "Invalid email address."});
	}
	// Check password
	if (data.password.value.length < 8 || data.password.value.length > 15
		|| !data.password.value.match(/^(?=.*[a-z])(?=.*[A-Z])(?=.*\d).{8,15}$/)) {
		return res.status(400).send({valid: false, message: "Passwords must be bewtween 8 and 16 characters and contains at least one number, one uppercase letter, one lowercase letter and one special character."});
	}
	if (data.password.value != data.pwdConfirm.value) {
		return res.status(400).send({valid: false, message: "Passwords mismatch !"});
	}
	try {
		// Hash password
		const salt = await bcrypt.genSalt()
		const hashedPwd = await bcrypt.hash(data.password.value, salt)
		const user = {
			username: data.username.value,
			email: data.email.value,
			password: hashedPwd,
		}
		// Handle avatar image
		if (data.avatar.file.bytesRead) {
			user.avatar = await req.server.imageUpload(data.avatar)
		} else {
			user.avatar = 'avatars/default_avatar'
		}
		const current = await req.server.models.User.create(user);
		// Create session token
		const accessToken = jwt.sign({id: current.id}, process.env.JWT_SECRET, { expiresIn: process.env.JWT_EXPIRES })
		const refreshToken = jwt.sign({id: current.id}, process.env.JWT_REFRESH_SECRET, { expiresIn: '1d' })
		current.token = refreshToken
		current.online = true
		await current.save()
		res.cookie('accessToken', accessToken, 	{ path: '/', maxAge: parseInt(process.env.JWT_EXPIRES) })
		res.cookie('id', current.id, { path: '/'})
		return res.status(201).send({valid: true, message: 'User created', user: current});
	} catch {
		return res.status(500).send({valid: false, message: 'Internal server error'});
	}
}

export const logout =  async (req, res) => {
	req.user.token = null
	req.user.online = false
	req.user.save()
	req.user = null
	res.clearCookie('id')
	res.clearCookie('accessToken')
	return res.status(204).send({})
}