const handleSignin = (request, response, database, bcrypt) => {
	const {password, email} = request.body;
	if (!email || !password) {
		return response.status(400).json('Incorrect signin submission');
	}
	database.select('hash', 'email').from('login')
	.where('email', '=', email)
	.then(loginData => {
		const isValid = bcrypt.compareSync(password, loginData[0].hash);
		if (isValid) {
			return database.select('*').from('users')
			.where('email','=', email)
			.then(userInfo => {
				response.status(200).json(userInfo[0]);
			})
		}
		else {
			response.status(400).json("Wrong password");
		} 
	})
	.catch(err => response.status(400).json("Can't find user"));	
}

module.exports = {
	handleSignin : handleSignin
};