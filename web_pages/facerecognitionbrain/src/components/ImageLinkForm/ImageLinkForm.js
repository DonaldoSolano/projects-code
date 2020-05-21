import React from 'react';
import './ImageLinkForm.css';

const ImageLinkForm = ({onInputChange,onButtonSubmit}) => {
	return (
		<div>
			<p className = 'f3'>{"Put an online face image url and let Emoticonify do it's magic!"}</p>
			<div className='center'>
				<div className= 'form center pa4 br3 shadow-5'>
					<input className= 'br--left br4 f4 pa2 w-70 center' placeholder="example.com/image.jpg" onChange= {onInputChange} type= 'text'/>
					<button className= 'br--right br4 w-30 grow f4 link ph3 pv2 dib black bg-light-green' onClick={onButtonSubmit}> <p className = 'tc f6'>Emoticonify!</p></button>			
				</div>
			</div>
		</div>
	);
}

export default ImageLinkForm;