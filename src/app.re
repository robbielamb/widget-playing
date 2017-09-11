[%bs.raw {|require('./app.css')|}];

open Bootstrap;

external logo : string = "./logo.svg" [@@bs.module];

let se = ReasonReact.stringToElement;

module Foo = {
  type action =
    | Toggle;
  type state = bool;
  let toggle (event: ReactEventRe.Mouse.t) => {
    Js.log event;
    Toggle
  };
  let component = ReasonReact.reducerComponent "Foo";
  let make ::message _children => {
    ...component,
    initialState: fun () => true,
    reducer: fun action state =>
      switch action {
      | Toggle =>
        ReasonReact.UpdateWithSideEffects (not state) (fun _self => Js.log "Reducer called")
      | _ => ReasonReact.SideEffects (fun _self => Js.log "Called again!")
      },
    render: fun {state, reduce} =>
      <Bootstrap.Alert color=Bootstrap.Alert.Color.Primary isOpen=state toggle=(reduce toggle)>
        <strong> (ReasonReact.stringToElement "Success") </strong>
        <p> (ReasonReact.stringToElement message) </p>
      </Bootstrap.Alert>
  };
};

/* module ModalExample = {
  type action =
    | Toggle;
  type state = bool;
  let toggle event => {
    Js.log2 "Toggling modal" event;
    Toggle
  };
  let component = ReasonReact.reducerComponent "ButtonExample";
  let make _children => {
    ...component,
    initialState: fun () => false,
    reducer: fun action state =>
      switch action {
      | Toggle => ReasonReact.Update (not state)
      },
    render: fun {state, reduce} =>
      <div>
        <Button color=Button.Color.Danger onClick=(reduce toggle)> (se "Launch Modal") </Button>
        <Modal isOpen=state toggle=(reduce toggle)>
          <ModalHeader toggle=(reduce toggle)> (se "Modal Header") </ModalHeader>
          <ModalBody> (se "This is the modal body where I can put stuff") </ModalBody>
          <ModalFooter>
            <Button color=Button.Color.Primary onClick=(reduce toggle)>
              (se "Do Something")
            </Button>
            <Button color=Button.Color.Secondary onClick=(reduce toggle)> (se "Cancel") </Button>
          </ModalFooter>
        </Modal>
      </div>
  };
}; */

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
      <Foo message="Here is message" />
      <div>
        <Bootstrap.Badge color=Bootstrap.Badge.Color.Primary> (se "Default") </Bootstrap.Badge>
      </div>
      <div>
        <Bootstrap.BreadCrumb>
          <Bootstrap.BreadCrumbItem> (se "home") </Bootstrap.BreadCrumbItem>
        </Bootstrap.BreadCrumb>
        <Bootstrap.BreadCrumb>
          <Bootstrap.BreadCrumbItem> (se "home") </Bootstrap.BreadCrumbItem>
          <Bootstrap.BreadCrumbItem active=true> (se "more") </Bootstrap.BreadCrumbItem>
        </Bootstrap.BreadCrumb>
      </div>
      <div>
        <Button color=Button.Color.Primary size=Button.Size.LG> (se "Primary") </Button>
        (se " ")
        <Button color=Button.Color.Secondary> (se "Secondary") </Button>
        (se " ")
        <Button color=Button.Color.Success> (se "Success") </Button>
        (se " ")
        <Button color=Button.Color.Info> (se "Info") </Button>
        (se " ")
        <Button color=Button.Color.Warning> (se "Warning") </Button>
        (se " ")
        <Button color=Button.Color.Danger> (se "Danger") </Button>
        (se " ")
        <Button color=Button.Color.Link> (se "Link") </Button>
      </div>
      /* <ModalExample /> */
    </div>
};