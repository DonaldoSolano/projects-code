import React from 'react';
import {validateEmail} from '../../utils/inputValidation.js';
import emoticonify from '../Media/emoticonify.svg';

class Signin extends React.Component {
	constructor (props) {
		super(props);
		this.state = {
			signInEmail: '',
			signInPassword: '',
			signInErrorMessage:'',
			signInPasswordErrorMessage:''
		}
	}

	componentDidMount() {
		document.addEventListener("keypress",this.submitSignInOnKeypress);
	}

	componentWillUnmount() {
  		document.removeEventListener("keypress",this.submitSignInOnKeypress);
	}	

	onEmailChange = (event) => {
		this.setState({
			signInEmail: event.target.value
		});
	}

	onPasswordChange = (event) => {
		this.setState({
			signInPassword: event.target.value
		});
	}

	onSubmitSignIn = () => {
		if (validateEmail(this.state.signInEmail)) {
			fetch('http://localhost:2000/signin', {
				method: 'post',
				headers: {'Content-Type': 'application/json'},
				body: JSON.stringify({
					email: this.state.signInEmail,
					password: this.state.signInPassword
				})
			})
			.then(response => response.json())
			.then(user => {
				if (user.id) {
					const loggedUser = JSON.parse(JSON.stringify(user));
					loggedUser['box'] = [];
					loggedUser['route'] = '';
					loggedUser['input'] = '';
					localStorage.setItem('id_a', JSON.stringify(loggedUser));
					this.props.loadUser(user);
					this.props.onRouteChange('frecscreen');
				}
				else {
					this.setState({signInPasswordErrorMessage: 'Wrong password or user'});
					document.getElementById("signInPasswordErrorStyle").style.display = "block";
				}
			})
			.catch(err =>{
				console.log(err);	
			});
		}
		else {
			this.setState({signInErrorMessage:"Nope, try something like 'example@domain.com' =)"});
			document.getElementById("signInErrorStyle").style.display = "block";
		}
	}

	submitSignInOnKeypress = (event) => {
		if (event.keyCode === 13) {
			this.onSubmitSignIn();
		}
	}

	render() {
		const {onRouteChange} = this.props;
		return(
			<article className="br3 ba dark-gray b--black-10 mv4 w-100 w-50-m w-25-l mw6 shadow-5 center">
				<main className='pa4 black-80'>
					<div className='measure'>
						<fieldset id='sign_up' className='ba b--transparent ph0 mh0'>
							<img alt = 'Emoticonify' src = {emoticonify}/>
							<p className='f2 fw6 ph0 mh0 ma0'>Sign In</p>
							<div className='mt3'>
								<label className='db fw6 lh-copy f6' htmlFor='email-address'>Email</label>
								<input onChange = {this.onEmailChange} className='pa2 input-reset ba bg-transparent hover-bg-black hover-white w-100' type='email' name='email-address'  id='email-address'/>
								<p id = "signInErrorStyle" className = "bg-red br3 f7 white">{this.state.signInErrorMessage}</p>
							</div>
							<div className='mv3'>
								<label className='db fw6 lh-copy f6' htmlFor='password'>Password</label>
								<input onChange = {this.onPasswordChange} className='b pa2 input-reset ba bg-transparent hover-bg-black hover-white w-100' type='password' name='password'  id='password'/>
								<p id = "signInPasswordErrorStyle" className = "bg-red br3 f7 white">{this.state.signInPasswordErrorMessage}</p>
							</div>
						</fieldset>
						<div className=''>
							<input className='b ph3 pv2 input-reset ba b--black bg-transparent grow pointer f6 dib' onClick = {this.onSubmitSignIn} type='submit' value='Sign in'/>
						</div>
						<div className='lh-copy mt3'>	
							<p className='f6 black'>Don't have an account? <a onClick = {() => onRouteChange('register')} href='#0' className='f6 link dim black db pointer'>Register</a></p>
						</div>
					</div>
				</main>
			</article>
		);
	}		
} 

export default Signin;