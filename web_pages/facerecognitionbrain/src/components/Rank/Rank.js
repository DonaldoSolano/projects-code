import React from 'react';

const Rank = ({name, entries}) => {
	return (
		<div>
			<div className = 'black f3'>
				{`Hello ${name}, your current Emotipoints are:`}
			</div>
			<div className = 'black f1'>
				{entries}
			</div>	
		</div>
	);
}

export default Rank;