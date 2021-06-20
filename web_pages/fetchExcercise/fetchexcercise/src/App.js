import React, {Component} from 'react';
import { connect } from 'react-redux';
import Catheader from './components/catsHeader.js';
import Factcomponent from './components/Factcomp.js';
import { requestFacts } from './actions.js';
import './App.css';

const mapStateToProps = state => {
  return {
    fact: state.requestFacts.fact,
    isPending: state.requestFacts.isPending,
    error: state.requestFacts.error
  };
}

const mapDispatchToProps = dispatch => {
  return {
    onRequestFacts: () => dispatch(requestFacts())
  }
}

class App extends Component {

  componentDidMount() {
    this.props.onRequestFacts();
  }
  
  render () {
    const {fact, isPending} = this.props;
    return (
      <div>
        <div className="App">
          <Catheader header = 'Did you know that?'></Catheader>
          <Factcomponent onRequestFacts={this.props.onRequestFacts} fact = {fact}/>
        </div>  
      </div>
    );         
  }
}

export default connect(mapStateToProps, mapDispatchToProps)(App);
