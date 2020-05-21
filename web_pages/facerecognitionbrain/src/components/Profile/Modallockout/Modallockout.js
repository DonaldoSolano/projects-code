import React from 'react';
import './Modallockout.css';

export class Modallockout extends React.Component {

	constructor(props){
		super(props);
		this.state = {}
	}

	onRequestAccountDelete = () => {
		fetch('http://localhost:2000/deleteLoggedUser', {
			method: 'delete',
			headers: {'Content-Type': 'application/json'},
			body: JSON.stringify({
				email: this.props.accountEmail,
			})
		})
		.then(response =>{
			if (response) {
				this.props.onRouteChange('signin');
			}
		})
	}

	onDenialAccountDelete = () => {
		document.querySelector('.displayModallockout').style.display = 'none';
	}

	render() {
		return (
			<div className = 'displayModallockout'>
				<article className="mw7 center ph3 ph5-ns tc br2 pv5 bg-washed-green dark-green mb5">
					<div className = 'w-100'>
					<h1 className="fw6 f3 f2-ns lh-title mt0 mb3">
							Are you sure you want to delete this account?
						</h1>
						<a onClick = {this.onRequestAccountDelete} className="f6 br-pill bg-dark-green no-underline washed-green ba b--dark-green grow pv2 ph3 dib mr3"href="#">
							Ok
						</a>
						<a onClick = {this.onDenialAccountDelete} className="f6 br-pill dark-green no-underline ba grow pv2 ph3 dib"href="#">
							Cancel
						</a>
					</div>
				</article>
			</div>
		);
	}			
}

