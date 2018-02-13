include WidgetPlaying.Bootstrap;

let code: string =
  [%bs.raw {|require('Examples/CollapseExample.re')|}] |> Examples.prepCode;

let se = ReasonReact.stringToElement;

module Collapser = {
  type action =
    | Toggle
    | Opened
    | Closed;
  type state = {
    isOpen: bool,
    status: string
  };
  let component = ReasonReact.reducerComponent("Collapser");
  let make = _children => {
    ...component,
    initialState: () => {isOpen: true, status: "Open"},
    reducer: (action, state) =>
      switch action {
      | Toggle =>
        ReasonReact.Update({
          isOpen: ! state.isOpen,
          status: ! state.isOpen ? "Opening..." : "Collapsing..."
        })
      | Opened => ReasonReact.Update({...state, status: "Open"})
      | Closed => ReasonReact.Update({...state, status: "Closed"})
      },
    render: ({state, send}) =>
      <div>
        <Button onClick=(_event => send(Toggle)) color=Button.Color.Primary>
          (se("Collapse"))
        </Button>
        <p> (se(state.status)) </p>
        <Collapse
          isOpen=state.isOpen
          onOpened=(_event => send(Opened))
          onClosed=(_event => send(Closed))>
          <Card>
            <Card.Header> (se("This is the card header")) </Card.Header>
            <Card.Body>
              (se("THis is card and some more and some more and some more!"))
            </Card.Body>
          </Card>
        </Collapse>
      </div>
  };
};

let component = ReasonReact.statelessComponent("CollapseExample");

let make = _children => {
  ...component,
  render: _self =>
    <Examples.Example title="Collapse">
      <Collapser />
      (Examples.exampleHighlight(code))
    </Examples.Example>
};