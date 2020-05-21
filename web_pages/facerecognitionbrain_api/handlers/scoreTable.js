const handleScoreTable = (request, response, database) => {
	database('users')
	.select('name', 'entries')
	.orderBy('entries', 'desc')
	.then(appUsers => {
		appUsers.length?response.status(200).json(appUsers):
		response.status(400).json("Couldn't load scores");	
	})
	.catch(err=>response.status(400).json(err));
}

module.exports = {
	handleScoreTable: handleScoreTable
};