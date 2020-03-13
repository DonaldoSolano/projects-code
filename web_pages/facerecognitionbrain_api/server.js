const express = require('express');
const cors = require('cors');
const app = express();
const bcrypt = require('bcrypt');
const bodyParser = require('body-parser');
const port = 2000;
const saltRounds = 10;

app.use(bodyParser.json());
app.use(cors());

const temporalDatabase = {
	users : [
		{
			id: '123',
			name: 'John',
			email: 'john@gmail.com',
			password : 'cookies',
			entries : 0,
			joined : new Date()
		},
		{
			id: '124',
			name: 'Sally',
			email: 'Sally@gmail.com',
			password : 'bananas',
			entries : 0,
			joined : new Date()
		}
	]
}

app.get('/',(request, response)=>{
	response.send(temporalDatabase.users);
});

app.get('/profile/:id',(request, response)=>{
	const { id } = request.params;
	let found = false;
	temporalDatabase.users.forEach(user => {
		if (user.id === id) {
			found = true;
			return response.json(user);
		}
	})
	if (!found) {
		response.status(400).json('User not found');
	}
});

app.post('/signin',(request, response)=>{
	let tryerChecker = 0;
	for (var i = 0; i < temporalDatabase.users.length; i++) {

		if (request.body.email === temporalDatabase.users[i].email && request.body.password === temporalDatabase.users[i].password ) {
			tryerChecker = 0;
			return response.status(200).json(temporalDatabase.users[i]);
		} else {
			tryerChecker++;
			continue;
		}
	}
	if (tryerChecker === temporalDatabase.users.length) {
		tryerChecker = 0;
		response.status(400).json('Error signing in');
	}
});

const registerDataChecker = data => {
	return typeof data === 'string' && data !== ''? true : false; 
}

app.post('/register',(request, response)=>{
	const {email, name, password} = request.body;

	let currentUsersQuantity = temporalDatabase.users.length;

	const validName = registerDataChecker(name);
	const validEmail = registerDataChecker(email);
	const validPassword = registerDataChecker(password);

	if (validName && validEmail && validPassword) {
		temporalDatabase.users.push({
			id: '125',
			name: name,
			email: email,
			password: password,
			entries: 0,
			joined: new Date()
		});
	} 

	if (temporalDatabase.users.length === currentUsersQuantity + 1) {
		response.status(200).json(temporalDatabase.users[temporalDatabase.users.length-1]);
	} else {
		response.status(400).json('Unsuccessful registration');
	}
});

app.put('/image',(request, response)=>{
	const { id } = request.body;
	let found = false;
	temporalDatabase.users.forEach(user => {
		if (user.id === id) {
			found = true;
			user.entries++;
			return response.json(user.entries);
		}
	})
	if (!found) {
		response.status(400).json('User not found');
	}
});

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


