import React from 'react';
import './Facerecognition.css';
 
const Facerecognition = ({Imageurl, box}) => {
	const faceRegions = box.map((face,i) =>{
			return <div key = {i} className= 'boundingBox' style = {{ top: face.topRow, right: face.rightCol, bottom: face.bottomRow, left: face.leftCol}}></div>
		});
	
	return(
		<div className= 'center ma'>
			<div className= 'absolute mt2'>
				<img id= 'inputimage' alt='' src={Imageurl} width= '500px' height= 'auto'/>	
				{faceRegions}
			</div>
		</div>
	);
}

export default Facerecognition;