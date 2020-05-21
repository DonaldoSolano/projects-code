import React from 'react';
import back from '../Media/back.svg';

export class ScoreTable extends React.Component {

	constructor(props) {
		super(props);
		this.state = {
			scoreUsers: []
		};
	}
	componentDidMount () {
		fetch('http://localhost:2000/scoreTable', {
			method: 'get'})
		.then(response => response.json())
		.then(users => {
			this.setState({scoreUsers:users});
		})
		.catch(err =>{
			console.log(err);	
		});
	}

	render () {
		const {onRouteChange} = this.props;
		return (
				<div className="pa4">
					<nav className = 'tl flex flex-row'>
				 		<a className="ml1 pointer" onClick = {() => onRouteChange('frecscreen')}>
				 			<img className = 'mw2' src = {back} />
				 		</a>
					</nav>
					<div className="overflow-auto">
						<table className="f6 w-100 mw8 center" cellSpacing="0">
							<tbody className="lh-copy">
								<tr>
									<th className="f2 fw6 bb b--black-20 pb3 pr3 ">User</th>
									<th className="f2 fw6 bb b--black-20 pb3 pr3 ">Score</th>
								</tr>
								{
									this.state.scoreUsers.map(scoreUser => {
										return(
											<tr>
												<td className="f4 pv3 pr3 bb b--black-20">{scoreUser.name}</td>
												<td className="f4 pv3 pr3 bb b--black-20">{scoreUser.entries}</td>
											</tr>
										);
									})
								}
							</tbody>
						</table>
					</div>
				</div>
		);
	}
}