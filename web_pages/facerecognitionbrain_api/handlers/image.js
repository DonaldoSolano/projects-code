const Clarifai = require('clarifai');  

const app = new Clarifai.App({
	apiKey: ''
});

const handleImage = (request, response, database) => {
	const { id } = request.body;
	database('users')
	.where('id', '=', id)
	.increment('entries', 1)
	.returning('entries')
	.then(entries => {
		response.status(200).json(entries[0]);
	})
	.catch(err=>response.status(400).json("Couldn't update entries"));
}


const handleApiCall = (request, response) => {
	const {input} = request.body;
	if (!input) {
		return response.status(400).json('Incorrect link submission');
	}
	app.models.predict(Clarifai.FACE_DETECT_MODEL, input)
	.then(data =>{
		response.status(200).json(data);
	})
	.catch(err => response.status(400).json(err));
}

module.exports = {
	handleImage: handleImage,
	handleApiCall : handleApiCall
};