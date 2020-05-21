const handleProfileID = (request, response, database) => {
	const { id } = request.params;
	database('users')
	.where({
		id: id
	})
	.select('name', 'entries')
	.then(appUsers => {
		appUsers.length?response.status(200).json(appUsers[0]):
		response.status(400).json('User not found');	
	})
	.catch(err=>response.status(400).json('User not found'));
}

module.exports = {
	handleProfileID: handleProfileID
};