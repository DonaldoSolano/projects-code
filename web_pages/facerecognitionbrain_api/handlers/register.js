const handleRegister = (request, response, database, bcrypt) => {
	const {email, name, password} = request.body;
	if (!email || !name || !password) {
		return response.status(400).json('Incorrect register submission');
	}
	const saltRounds = 10;
	const hash = bcrypt.hashSync(password, saltRounds);
	database.transaction(trx => {
		trx.insert({
			email: email,
			hash: hash
		 })
		.into('login')
		.returning('email')
		.then(loginEmail => {
			return trx('users')
			.returning('*')
			.insert({
				email:loginEmail[0],//This one returns an array of length 1, so we grab the 0 position to get the raw email
				name: name,
				joined: new Date()
			})
			.then(user => {
				response.json(user[0]);//Making sure is not an array, and, in case of so, returning the first one.
			})
		})
		.then(trx.commit)
		.catch(trx.rollback);
	}).catch(err => response.status(400).json('Unable to register'));
}

module.exports = {
	handleRegister: handleRegister
};