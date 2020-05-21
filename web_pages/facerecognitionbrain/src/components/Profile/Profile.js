import React from 'react';
import back from '../Media/back.svg';
import brain from '../Media/brain.png';
import close from '../Media/close.svg';
import {Modallockout} from './Modallockout/Modallockout.js';
import './Profile.css';

export class Profile extends React.Component {
	constructor(props){
		super(props);
		this.state = {};
	}

	onPressDeleteAccountButton = () => { 
		document.querySelector('.displayModallockout').style.display = 'block';
	}

	render() {
		const {ProfileInfo, onRouteChange} = this.props;
		return(
			<div>
				<Modallockout accountEmail = {ProfileInfo.email}  onRouteChange = {onRouteChange}/>
				<nav className = 'tl flex flex-row'>
			 		<a className="ml4 pointer" onClick = {() => onRouteChange('frecscreen')}>
			 			<img className = 'mw2' src = {back} />
			 		</a>
				</nav>
				<article className="mw5 center bg-washed-green br3 pa3 pa4-ns mv3 ba b--black-10">
					<div className="tc">
						<img src= {brain} className="br-100 h4 w4 dib ba b--black-05 pa2" title="You"/>
						<h1 className="f3 fw6 black mb2">{ProfileInfo.name}</h1>
						<h2 className="f5 fw6 black fw4 gray mt0">{`${ProfileInfo.entries} Emotipoints`}</h2>
						<h2 className="f5 fw6 black fw4 gray mt0">{`Joined: ${ProfileInfo.joined}`}</h2>
  					</div>
  					<div onClick = {this.onPressDeleteAccountButton} className = 'deleteAccountButtonStyle fr pointer'>
  						<img className = 'mw1' src = {close}/>
  					</div>
				</article>
			</div>
		);
	}
}