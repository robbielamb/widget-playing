[%bs.raw {|require('./app.css')|}];


external logo : string = "./logo.svg" [@@bs.module];

let component = ReasonReact.statelessComponent "App";

let make ::message _children => {
  ...component,
  render: fun _self =>
    <div className="App">
      <div className="App-header">
        <img src=logo className="App-logo" alt="logo" />
        <h2> (ReasonReact.stringToElement message) </h2>
      </div>
      <p className="App-intro">
        (ReasonReact.stringToElement "To get started, edit")
        <code> (ReasonReact.stringToElement " src/App.re ") </code>
        (ReasonReact.stringToElement "and save to reload.")
      </p>
      <Bootstrap.Alert color=Bootstrap.Alert.Color.Success> 
         <strong> (ReasonReact.stringToElement "Success") </strong>
      </Bootstrap.Alert>
    </div>
};

module Foo = {
  type action =
    | Click
    | Update;
  type state =
    | Int;
  let component = ReasonReact.reducerComponent "Foo";
  let make ::message _children => {
    ...component,
    initialState: fun () => 0,
    reducer: fun action state =>
      switch action {
      | Click => ReasonReact.UpdateWithSideEffects 0 (fun _self => Js.log "Reducer called")
      | _ => ReasonReact.SideEffects (fun _self => Js.log "Called again!")
      },
    render: fun {state} => <div> (ReasonReact.stringToElement message) </div>
  };
};