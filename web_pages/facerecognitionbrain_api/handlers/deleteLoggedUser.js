const handleDeleteLoggedUser = (request, response, database) => {
	const {email} = request.body;
	database.transaction(trx => {
		trx('users')
		.where('email', '=', email)
		.del()
		.then(loginEmail => {
			return trx('login')
			.where('email', '=', email)
			.del()
			.then(response.status(200).json('User deleted'))
		})
		.then(trx.commit)
		.catch(trx.rollback);
	}).catch(err => response.status(400).json('Unable to delete'));	
}

module.exports = {
	handleDeleteLoggedUser : handleDeleteLoggedUser
};