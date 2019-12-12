import React from 'react';
import './Facerecognition.css';

const Facerecognition = ({Imageurl, box}) => {
	return(
		<div className= 'center ma'>
			<div className= 'absolute mt2'>
				<img id= 'inputimage' alt='' src={Imageurl} width= '500px' height= 'auto'/>	
				<div className= 'boundingBox' style = {{ top: box.topRow, right: box.rightCol, bottom: box.bottomRow, left: box.leftCol}}></div>
			</div>
		</div>
	);
}

export default Facerecognition;