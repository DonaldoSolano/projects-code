import React, {Component} from 'react';
import Navigation from '../components/Navigation/Navigation.js';
import Logo from '../components/Logo/Logo.js';
import ImagelinkForm from '../components/ImageLinkForm/ImageLinkForm.js';
import Rank from '../components/Rank/Rank.js';
import Facerecognition from '../components/Facerecognition/Facerecognition.js';
import Signin from '../components/SignIn/SignIn.js';
import Register from '../components/Register/Register.js';
import Particles from 'react-particles-js';
import {Particlesconfig} from '../components/Particlesconfig/Particlesconfig.js';
import Clarifai, {FACE_DETECT_MODEL} from 'clarifai';
import './App.css';

const app = new Clarifai.App({
	apiKey: '405069c830254b7fa8b2a5f263e5dded'
});

class App extends Component {
	constructor() {
		super();
		this.state = {
			input: '',
			imageUrl: '',
			box: {},
			route: 'signin',
			isSignedIn: false 
		}
	}

	calculateFaceLocation = (data) => {
		const clarifaiFace = data.outputs[0].data.regions[0].region_info.bounding_box;
		const image = document.getElementById('inputimage');
		const width = Number(image.width);
		const height = Number(image.height);
		return {
			leftCol: clarifaiFace.left_col * width,
			topRow: clarifaiFace.top_row * height,
			rightCol: width - (clarifaiFace.right_col * width),
			bottomRow: height - (clarifaiFace.bottom_row * height)
		}
	}

	displayFaceBox = (box) => {
		this.setState({box: box});
	}

	onInputChange = (event) => {
		this.setState({input:event.target.value});
	}

	onButtonSubmit = (event) => {
		this.setState({imageUrl: this.state.input});
		app.models.predict(FACE_DETECT_MODEL, this.state.input)
			.then(response => {
		    	this.displayFaceBox(this.calculateFaceLocation(response))
		    })
		    .catch(err => console.log(err)
		);
	}

	onRouteChange = (screen) => {
		if (screen === 'frecscreen') {this.setState({isSignedIn:true})}
			else if (screen === 'signin') {this.setState({isSignedIn:false})}
		this.setState({route:screen});
	}

	render () {
		return (
			<div className = "App">
				<Particles className = "particles" params = {Particlesconfig}/>
				<Navigation onRouteChange = {this.onRouteChange} isSignedIn = {this.state.isSignedIn}/>
				{this.state.route === 'signin'? <Signin onRouteChange = {this.onRouteChange}/>:
				(this.state.route === 'frecscreen'?
				<div>
					<Logo/>
					<Rank/>
					<ImagelinkForm onInputChange = {this.onInputChange} onButtonSubmit = {this.onButtonSubmit}/>
					<Facerecognition Imageurl= {this.state.imageUrl} box = {this.state.box} />
				</div>:
				<div>
					<Register onRouteChange = {this.onRouteChange}/>
				</div>
				)
				}	
			</div>
  		);
  	}
}

export default App;
