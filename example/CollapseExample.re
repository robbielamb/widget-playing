include WidgetPlaying.Bootstrap;

let code: string = [%bs.raw {|require('Examples/CollapseExample.re').default|}] |> Examples.prepCode;

let se = React.string;

module Collapser = {
  type action =
    | Toggle
    | Opened
    | Closed;
  type state = {
    isOpen: bool,
    status: string,
  };

  let reducer = (state, action) : state => {
 switch (action) {
      | Toggle => {isOpen: !state.isOpen, status: !state.isOpen ? "Opening..." : "Collapsing..."}
      | Opened => {...state, status: "Open"}
      | Closed => {...state, status: "Closed"}
      }
  };

  [@react.component]
  let make = () => {
    
  
    let (state, dispatch) = React.useReducer(reducer, {isOpen: true, status: "Open"});
    
      <div>
        <Button onClick={_event => dispatch(Toggle)} color=Button.Color.Primary> {se("Collapse")} </Button>
        <p> {se(state.status)} </p>
        <Collapse isOpen={state.isOpen} onOpened={_event => dispatch(Opened)} onClosed={_event => dispatch(Closed)}>
          <Card>
            <Card.Header> {se("This is the card header")} </Card.Header>
            <Card.Body> {se("THis is card and some more and some more and some more!")} </Card.Body>
          </Card>
        </Collapse>
      </div>
    };
  };



[@react.component]
let make = () => {
 
    <Examples.Example title="Collapse"> <Collapser /> {Examples.exampleHighlight(code)} </Examples.Example>
};
