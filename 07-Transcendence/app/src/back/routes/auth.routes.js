import { register, login, logout } from "../controllers/auth.controller.js"
import { github, githubCallback, google, googleCallback } from "../controllers/auth.remote.controller.js"
import {  tfaSMS, tfaMail, qrCode, tfaVerify, tfaRefresh } from "../controllers/auth.twoFactors.controller.js"

export default function authRoutes(app) {
	app.post('/api/register', register);
	app.post('/api/login', login);
	app.post('/api/logout', logout);

	// authRemote routes
	app.get('/auth/github', github);
	app.get('/auth/github/callback', githubCallback);

	app.get('/auth/google', google);
	app.get('/auth/google/callback', googleCallback);

	// 2FA routes
	app.post('/auth/tfa/sms', tfaSMS);
	app.get('/auth/tfa/mail/:login', tfaMail);
	app.get('/auth/tfa/qrcode', qrCode);
	app.get('/auth/tfa/refresh', tfaRefresh);
	app.post('/auth/tfa/verify', tfaVerify);
}