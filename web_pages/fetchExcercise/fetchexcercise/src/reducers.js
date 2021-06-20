import {REQUEST_FACTS_PENDING, REQUEST_FACTS_SUCCESS, REQUEST_FACTS_FAILED } from './constants.js';

const initialStateFacts = {
	isPending: false,
	fact: [],
	error: ''
}

export const requestFacts = (state =initialStateFacts, action={}) => {
	switch (action.type) {
		case REQUEST_FACTS_PENDING:
			return Object.assign({},state, {isPending:true})
		case REQUEST_FACTS_SUCCESS:
			return Object.assign({}, state, { fact: action.payload, isPending: false})
		case REQUEST_FACTS_FAILED:
			return Object.assign({}, state, { error: action.payload, isPending: false})
		default:
			return state;
	}	
}