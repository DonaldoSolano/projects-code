import {REQUEST_FACTS_PENDING, REQUEST_FACTS_SUCCESS, REQUEST_FACTS_FAILED } from './constants.js'; 

export const requestFacts = () => (dispatch) => {
	dispatch({ type: REQUEST_FACTS_PENDING });
	fetch('https://catfact.ninja/fact?max_length=140').then(response => response.json())
	.then(data => dispatch({ type: REQUEST_FACTS_SUCCESS, payload: data }))
	.catch(error => dispatch ({ type: REQUEST_FACTS_FAILED, payload: error }))
}
