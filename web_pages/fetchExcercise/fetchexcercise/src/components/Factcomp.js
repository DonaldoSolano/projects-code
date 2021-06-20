import React from 'react';
import './Factcomp.css';
const Factcomponent = ({fact,onRequestFacts}) => {
	return (
		<div className="modal">
			<p className="message">
				{fact.fact}
			</p>
			<div className="options">
				<button className="btn" onClick = {onRequestFacts}>Cool!</button>
			</div>
	  </div>
	);
}

export default Factcomponent;