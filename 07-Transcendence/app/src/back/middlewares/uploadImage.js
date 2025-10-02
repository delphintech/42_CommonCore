import { v2 as cloudinary } from 'cloudinary';

// Cloudinary and mutler registration for photos
cloudinary.config({ 
	cloud_name: process.env.CLOUDY_NAME, 
	api_key: process.env.CLOUDY_API_KEY,
	api_secret: process.env.CLOUDY_API_SECRET
});

export const imageUpload = async (image) => {
	if (!image) {
		return "default_avatar"
	}

	let isUrl = false
	if (typeof image === "string") {
		const s = image.trim().toLowerCase();
		isUrl = s.startsWith("http://") || s.startsWith("https://");
	}

	let result;
	if (!isUrl) {
		const buffer = await image.toBuffer();
		result = await new Promise((resolve, reject) => {
			const stream = cloudinary.uploader.upload_stream(
				{ folder: 'avatars' },
				(error, result) => {
				if (error) return reject(error);
				resolve(result);
			})
			stream.end(buffer)
		})
	} else {
		result = await cloudinary.uploader.upload(image, { folder: 'avatars' });
	}
	return result.public_id
}