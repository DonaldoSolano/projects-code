 const profileID = require('./handlers/profileID');
const register = require('./handlers/register');
const signin = require('./handlers/signin');
const image = require('./handlers/image');
const score = require('./handlers/scoreTable');
const deleteUser = require('./handlers/deleteLoggedUser');
const express = require('express');
const cors = require('cors');
const app = express();
const knex = require('knex')
const database = knex({
	client: 'pg',
	connection: {
		host : '127.0.0.1',
		user : 'postgres',
		password : 'Dsolanon96',
		database : 'smart-brain'
	}
});
const bcrypt = require('bcrypt');
const bodyParser = require('body-parser');
const port = 2000;

app.use(bodyParser.json());
app.use(cors());

app.get('/profile/:id', (request, response) => {profileID.handleProfileID(request, response, database)});

app.delete('/deleteLoggedUser', (request, response) => {deleteUser.handleDeleteLoggedUser(request, response, database)});

app.get('/scoreTable', (request, response) => {score.handleScoreTable(request, response, database)});

app.post('/signin', (request, response) => {signin.handleSignin(request, response, database, bcrypt)});

app.post('/register', (request, response)=>{register.handleRegister(request, response, database, bcrypt)});

app.put('/image', (request, response)=>{image.handleImage(request, response, database)});

app.post('/imageurl', (request, response)=>{image.handleApiCall(request, response)});

app.listen(port, () => {
	console.log(`Server is running on port: ${port}`);
});

/*
-----EndPoints-----
/ --> res = This is working
/signin --> POST = success/fail
/register --> POST = user
/profile/:userId --> GET = user
/image --> PUT --> user 
*/

