const express = require('express');
const app = express();
//const bodyParser = require('body-parser');
const port = 2000;
//app.use(bodyParser);
app.get('/',(request, response)=>{
	response.send('GET request working');
});
app.listen(port, () => {
	console.log(`Server is running on port: ${port}`);
});