import React from 'react';
import './Register.css';
import {validateEmail} from '../../utils/inputValidation.js';

class Register extends React.Component {
	constructor(props) {
		super(props);
		this.state = {
			RegisterName:'',
			RegisterEmail:'',
			RegisterPassword:'',
			ErrorMessage:''
		}
	}

	componentDidMount() {
  		document.addEventListener("keypress",this.submitSignInOnKeypress);
	}

	componentWillUnmount() {
  		document.removeEventListener("keypress",this.submitSignInOnKeypress);
	}

	submitSignInOnKeypress = (event) => {
		if (event.keyCode === 13) {
			this.onSubmitRegister();
		}
	}

	onNameChange = (event) => {
		this.setState({
			RegisterName: event.target.value
		});
	}

	onEmailChange = (event) => {
		this.setState({
			RegisterEmail: event.target.value
		});
	}

	onPasswordChange = (event) => {
		this.setState({
			RegisterPassword: event.target.value
		});
	}

	onSubmitRegister = () => {
		if (validateEmail(this.state.RegisterEmail)) {
			fetch('http://localhost:2000/register', {
				method: 'post',
				headers: {'Content-Type': 'application/json'},
				body: JSON.stringify({
					name: this.state.RegisterName,
					email: this.state.RegisterEmail,
					password: this.state.RegisterPassword
				})
			})
			.then(response => response.json())
			.then(user => {
				if (user.id) {
					localStorage.setItem('id_a', JSON.stringify(user));
					this.props.loadUser(user);
					this.props.onRouteChange('frecscreen');
				}
			}).catch(err =>{
				this.setState({ErrorMessage:err});
				document.getElementById("errorStyle").style.display = "block";
			});
		}
		else {
			this.setState({ErrorMessage:"Nope, try something like 'example@domain.com' =)"});
			document.getElementById("errorStyle").style.display = "block";
		}
	}

	render(){
		return(
			<article className="br3 ba dark-gray b--black-10 mv4 w-100 w-50-m w-25-l mw6 shadow-5 center">
				<main className='pa4 black-80'>
					<div className='measure'>
						<fieldset id='sign_up' className='ba b--transparent ph0 mh0'>
							<legend className='f1 fw6 ph0 mh0'>Register</legend>
							<div className='mt3'>
								<label className='db fw6 lh-copy f6' htmlFor='name'>Name</label>
								<input onChange = {this.onNameChange} className='pa2 input-reset ba bg-transparent hover-bg-black hover-white w-100' type='text' name='name'  id='name'/>
							</div>
							<div className='mt3'>
								<label className='db fw6 lh-copy f6' htmlFor='email-address'>Email</label>
								<input onChange = {this.onEmailChange} className='pa2 input-reset ba bg-transparent hover-bg-black hover-white w-100' type='email' name='email-address'  id='email-address'/>
								<p id = "errorStyle" className = "bg-red br3 f7 white">{this.state.ErrorMessage}</p>
							</div>
							<div className='mv3'>
								<label className='db fw6 lh-copy f6' htmlFor='password'>Password</label>
								<input onChange = {this.onPasswordChange} className='b pa2 input-reset ba bg-transparent hover-bg-black hover-white w-100' type='password' name='password'  id='password'/>
							</div>
						</fieldset>
						<div className=''>
							<input className='b ph3 pv2 input-reset ba b--black bg-transparent grow pointer f6 dib pointer' onClick = {this.onSubmitRegister} type='submit' value='Register'/>
						</div>
					</div>
				</main>
			</article>
		);	
	}
}
export default Register;