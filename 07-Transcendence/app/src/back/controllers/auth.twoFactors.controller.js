import qrcode from "qrcode"
import { totp, authenticator } from "otplib"
import jwt from "jsonwebtoken"
import twilio from "twilio"
import { Resend } from "resend"

export const tfaSMS = async (req, res) => {
	const client = twilio(
		process.env.TWILIO_ACCOUNT_SID,
		process.env.TWILIO_AUTH_TOKEN
	)
	try {
		const phone = req.body
		if (!phone || !phone.match(/^(\+33|0)[67]\d{8}$/)) {
			return res.status(401).send({valid: false, message: 'Please provide a valid phone number'});
		}
		const user_id = req.cookies.id
		const user = await req.server.models.User.findByPk(user_id)
		if (!user_id || !user) {
			return res.status(401).send({valid: false, message: 'No current user'});
		}
		const token = totp.generate(user.totp, { step: 300, digits: 6 })
		const data = await client.messages.create({
			body: `Your verification code for Transcendance: ${token}`,
			from: process.env.TWILIO_SENDER,
			to: phone
		});
		return res.status(200).send({ valid: true, message: `Your code has been sent to ${phone}` })
	} catch (err) {
		console.log(err)
		return res.status(500).send({valid: false, message: 'Internal server error'});
	}
}

export const tfaMail = async (req, res) => {
	try {
		let user
		if (req.params.login) {
			user = await req.server.models.User.findOne({ where: { username: req.params.login } })
			if (!user) {
				return res.status(401).send({valid: false, message: 'No user exists with this login'});
			}
			if (user.auth != "local") {
				return res.status(401).send({valid: false, message: 'You are using remote auth to connect, not password'});
			}
			res.cookie('id', user.id, { path: '/'})
			await user.update({ totp: authenticator.generateSecret() })
		} else {
			const user_id = req.cookies.id
			user = await req.server.models.User.findByPk(user_id)
			if (!user_id || !user) {
				return res.status(401).send({valid: false, message: 'No current user'});
			}
		}
		const resend = new Resend(process.env.RESEND_TOKEN);
		const token = totp.generate(user.totp, { step: 300, digits: 6 })
		await resend.emails.send({
			from: '"Transcendance" <onboarding@resend.dev>',
			to: user.email,
			subject: "Login to transcendance",
			html: `<div style="font-family: Arial, sans-serif; padding: 20px;">
				<h2 style="color: #B07734;">Your 2FA Code for Transcendance</h2>
				<p style="font-size: 16px;">Use the following code to log in:</p>
				<div style="color: #613114; font-size: 24px; font-weight: bold; margin-top: 10px;">${token}</div>
			</div>`
		})
		return res.status(200).send({ valid: true, message: `Your code has been sent to ${user.email}` })
	} catch (err) {
		console.log(err)
		return res.status(500).send({valid: false, message: 'Internal server error'});
	}
}

export const qrCode = async (req, res) => {
	try {
		const user_id = req.cookies.id
		const user = await req.server.models.User.findByPk(user_id)
		if (!user_id || !user) {
			res.status(401).send({valid: false, message: 'No current user'});
		}
		if (!user.totp) { 
			await user.update({ totp: authenticator.generateSecret() })
		}
		const otpauth = authenticator.keyuri(user.username, "Transcendance", user.totp)
		const image = await qrcode.toDataURL(otpauth)
		return res.status(200).send({ qrcode: image })
	} catch (err) {
		console.log(err)
		return res.status(500).send({valid: false, message: 'Internal server error'});
	}
}

export const tfaRefresh = async (req, res) => {
	try {
		const user_id = req.cookies.id
		const user = await req.server.models.User.findByPk(user_id)
		if (!user_id || !user) {
			res.status(401).send({valid: false, message: 'No current user'});
		}
		await user.update({ totp: authenticator.generateSecret() })
		const otpauth = authenticator.keyuri(user.username, "Transcendance", user.totp)
		const image = await qrcode.toDataURL(otpauth)
		return res.status(200).send({ qrcode: image })
	} catch (err) {
		console.log(err)
		return res.status(500).send({valid: false, message: 'Internal server error'});
	}
}

export const tfaVerify = async (req, res) => {
	try {
		const code = req.body
		const user_id = req.cookies.id
		const user = await req.server.models.User.findByPk(user_id)
		if (!user_id || !user) {
			return res.status(401).send({valid: false, message: 'No current user'});
		}
		const check = authenticator.verify({
			token: code, 
			secret: user.totp,
			window: 1
		}) || totp.check(code, user.totp, { step: 300, digits: 6 })
		if (check) {
			const accessToken = jwt.sign({id: user.id}, process.env.JWT_SECRET, { expiresIn: process.env.JWT_EXPIRES })
			const refreshToken = jwt.sign({id: user.id}, process.env.JWT_REFRESH_SECRET, { expiresIn: '1d' })
			await user.update({ token: refreshToken, online: true })
			res.cookie('accessToken', accessToken, 	{ path: '/', maxAge: parseInt(process.env.JWT_EXPIRES) })
			res.cookie('id', user.id, { path: '/'})
			return res.status(200).send({valid: true, message: 'Logged in !', user: user.get({plain: true})});
		} else {
			return res.status(401).send({valid: false, message: 'Wrong code !', user: user.get({plain: true})});
		}
	} catch (err) {
		console.log(err)
		return res.status(500).send({valid: false, message: 'Internal server error'});
	}
}