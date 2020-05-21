import React from 'react';

const Navigation = ({onRouteChange, isSignedIn}) => {
	 	if(isSignedIn === true){
	 		return(
	 			<nav style = {{display: 'flex', justifyContent: 'flex-end'}}>
	 				<p className = 'pr3 black grow'>
		 				<a className=" shadow-1 f3  no-underline br-pill ph3 pv2 mb2 pointer" onClick = {() => onRouteChange('scoretable')}>Scores</a>
		 			</p>
		 			<p className = 'pr3 black grow'>
		 				<a className=" shadow-1 f3  no-underline br-pill ph3 pv2 mb2 pointer" onClick = {() => onRouteChange('signin')}>Sign Out</a>
		 			</p>
				</nav>
	 		);
	 		
	 	} else if (isSignedIn === false) {
	 		return(
	 			<nav style = {{display: 'flex', justifyContent: 'flex-end'}}>
					<p className= ' pr1 black grow' >
						<a className=" shadow-1 f3  no-underline br--left br3 ph3 pv2 mb2 pointer" onClick = {() => onRouteChange('signin')}>Sign In</a>
					</p>

					<p className= 'pr3 black grow'>
						<a className=" shadow-1 f3  no-underline br--right ph3 br3 pv2 mb2 pointer" onClick = {() => onRouteChange('register')}>Register</a>
					</p>
				</nav>
	 		);
	 			
	 	}
		
		
		
}

export default Navigation;