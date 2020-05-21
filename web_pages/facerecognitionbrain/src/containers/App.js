import React, {Component} from 'react';
import Navigation from '../components/Navigation/Navigation.js';
import Logo from '../components/Logo/Logo.js';
import ImagelinkForm from '../components/ImageLinkForm/ImageLinkForm.js';
import Rank from '../components/Rank/Rank.js';
import Facerecognition from '../components/Facerecognition/Facerecognition.js';
import Signin from '../components/SignIn/SignIn.js';
import Register from '../components/Register/Register.js';
import {Footer} from '../components/Footer/Footer.js';
import {ScoreTable} from '../components/ScoreTable/ScoreTable.js';
import {Profile} from '../components/Profile/Profile.js';
import Particles from 'react-particles-js';
import {Particlesconfig} from '../components/Particlesconfig/Particlesconfig.js';
import {imageUrlValidation} from '../utils/inputValidation.js';
import NotFound from '../components/Media/NotFound.png';
import './App.css';

const initialState = {
	input: '',
	imageUrl: '',
	box: [],
	route: 'signin',
	isSignedIn: false,
	user: {
		id: '',
		name: '',
		email: '',
		password : '',
		entries : 0,
		joined : ''
	} 
}

class App extends Component {
	constructor() {
		super();
		this.state = initialState;
	}


	loadUser = data => {
		this.setState({
			user: {
				id: data.id,
				name: data.name,
				email: data.email,
				password: data.password,
				entries: data.entries,
				joined: data.joined
			}
		});
	}

	calculateFaceLocation = (data) => {
		const imageFaceRegionsData = data.outputs[0].data.regions;
		const image = document.getElementById('inputimage');
		const width = Number(image.width);
		const height = Number(image.height);
		const clarifaiFace = imageFaceRegionsData.map((face,i) => {
			return ({
				leftCol: face.region_info.bounding_box.left_col * width,
				topRow: face.region_info.bounding_box.top_row * height,
				rightCol: width - (face.region_info.bounding_box.right_col * width),
				bottomRow: height - (face.region_info.bounding_box.bottom_row * height)
			});
		});

		return clarifaiFace;
	}

	displayFaceBox = (box) => {
		this.setState({box: box});
	}

	onInputChange = (event) => {
		this.setState({input:event.target.value});
	}

	onButtonSubmit = (event) => {
		const loggedUser = localStorage.getItem('id_a');
		const localUser = JSON.parse(loggedUser);
		if (imageUrlValidation(this.state.input)) {
			localUser['input'] = this.state.input;
			this.setState({imageUrl: this.state.input});
			fetch('http://localhost:2000/imageurl', {
					method: 'post',
					headers: {'Content-Type': 'application/json'},
					body: JSON.stringify({
					input:this.state.input
				})
			})
			.then(response=>response.json())
			.then(response => {
				if (response !== 'Incorrect link submission') {
					fetch('http://localhost:2000/image', {
						method: 'put',
						headers: {'Content-Type': 'application/json'},
						body: JSON.stringify({
							id:this.state.user.id
						})
					})
					.then(response =>response.json())
					.then(entries =>
						{
							if(entries) {
								localUser['entries'] = entries;
								localStorage.setItem('id_a', JSON.stringify(localUser));
								this.setState(Object.assign(this.state.user, {entries:entries}));
							}
						}
					)
					.catch(err => console.log(err));
				}
				else {
					this.setState(Object.assign(this.state.user, {entries:this.state.user.entries}));
				}
			    this.displayFaceBox(this.calculateFaceLocation(response));
			    localUser['box'] = this.state.box;
				localStorage.setItem('id_a', JSON.stringify(localUser));
			}).catch(err => console.log(err));
		}
		else {

			if (this.state.box.length >= 1) {
				this.setState({box: [],imageUrl: NotFound});
			}
			else {
				this.setState({imageUrl: NotFound});
			}
		}
		
	}

	componentDidMount() {
		if(!!localStorage.getItem('id_a')){
			const loggedUser = localStorage.getItem('id_a');
			const localUser = JSON.parse(loggedUser);
			this.loadUser(localUser);
			localStorage.setItem('id_a', JSON.stringify(localUser));
    		this.setState({
    			imageUrl:localUser.input,
    			box:localUser.box,
    			route:localUser.route,
    			isSignedIn:true
    		});
  		}
	}

	onRouteChange = (screen) => {
		if (screen === 'frecscreen') {this.setState({isSignedIn:true})}
			else if (screen === 'signin') {
				localStorage.removeItem('id_a');
				this.setState(initialState);
			}
		this.setState({route:screen});

		if(!!localStorage.getItem('id_a')){
			const loggedUser = localStorage.getItem('id_a');
			const localUser = JSON.parse(loggedUser);
			localUser['route'] = screen;
			localStorage.setItem('id_a', JSON.stringify(localUser));
		}
	}

	routeRenderer = (param) => {
		switch (param) {
			case 'signin':
				return <Signin loadUser={this.loadUser} onRouteChange = {this.onRouteChange}/>
			break;

			case 'frecscreen':
				return(
					<div>
						<Logo onRouteChange = {this.onRouteChange}/>
						<Rank name={this.state.user.name} entries={this.state.user.entries}/>
						<ImagelinkForm onInputChange = {this.onInputChange} onButtonSubmit = {this.onButtonSubmit}/>
						<Facerecognition Imageurl= {this.state.imageUrl} box = {this.state.box} />
					</div>
				);
			break;

			case 'register':
				return <Register loadUser = {this.loadUser} onRouteChange = {this.onRouteChange}/>
			break;

			case 'scoretable':
				return <ScoreTable onRouteChange = {this.onRouteChange}/>
			break;

			case 'profile':
				return <Profile ProfileInfo = {this.state.user} onRouteChange = {this.onRouteChange}/>
			break;
		}
	}

	render () {
		return (
			<div className = "App">
				<Particles className = "particles" params = {Particlesconfig}/>
				<Navigation onRouteChange = {this.onRouteChange} isSignedIn = {this.state.isSignedIn}/>
				{
					<div>
						{this.routeRenderer(this.state.route)}
					</div>
				}
				<Footer/>	
			</div>
  		);
  	}
}

export default App;
