[%bs.raw {|require('./app.css')|}];

open Bootstrap;

external logo : string = "./logo.svg" [@@bs.module];

let se = ReasonReact.stringToElement;

module Example = {
  let component = ReasonReact.statelessComponent "Example";
  let make ::title (children: array ReasonReact.reactElement) => {
    ...component,
    render: fun _self => {
      let title = <h3> (se title) </h3>;
      let _ = Js.Array.unshift title children;
      let col = ReasonReact.element (Layout.Col.make children);
      <Layout.Row className="mb-4 border p-2"> col </Layout.Row>
    }
  };
};

module AlertExample = {
  type action =
    | Toggle;
  type state = bool;
  let toggle (event: ReactEventRe.Mouse.t) => {
    Js.log event;
    Toggle
  };
  let component = ReasonReact.reducerComponent "AlertExample";
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
      <Example title="Alerts">
        <Bootstrap.Alert color=Bootstrap.Alert.Color.Primary isOpen=state toggle=(reduce toggle)>
          <strong> (ReasonReact.stringToElement "Success") </strong>
          <p> (ReasonReact.stringToElement message) </p>
        </Bootstrap.Alert>
      </Example>
  };
};

module ModalExample = {
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
      <Example title="Modal">
        <Button color=Button.Color.Danger onClick=(reduce toggle)> (se "Launch Modal") </Button>
        <Modal isOpen=state toggle=(reduce toggle)>
          <Modal.Header toggle=(reduce toggle)> (se "Modal Header") </Modal.Header>
          <Modal.Body> (se "This is the modal body where I can put stuff") </Modal.Body>
          <Modal.Footer>
            <Button color=Button.Color.Primary onClick=(reduce toggle)>
              (se "Do Something")
            </Button>
            <Button color=Button.Color.Secondary onClick=(reduce toggle)> (se "Cancel") </Button>
          </Modal.Footer>
        </Modal>
      </Example>
  };
};

let component = ReasonReact.statelessComponent "App";

let make ::message _children => {
  ...component,
  render: fun _self =>
    <Layout.Container>
      <Example title="Example example"> (se "An Example") </Example>
      <AlertExample message="Here is message" />
      <Example title="Badges">
        <Bootstrap.Badge color=Bootstrap.Badge.Color.Primary> (se "Default") </Bootstrap.Badge>
      </Example>
      <Example title="Breadcrumbs">
        <Bootstrap.BreadCrumb>
          <Bootstrap.BreadCrumb.Item> (se "home") </Bootstrap.BreadCrumb.Item>
        </Bootstrap.BreadCrumb>
        <Bootstrap.BreadCrumb>
          <Bootstrap.BreadCrumb.Item> (se "home") </Bootstrap.BreadCrumb.Item>
          <Bootstrap.BreadCrumb.Item active=true> (se "more") </Bootstrap.BreadCrumb.Item>
        </Bootstrap.BreadCrumb>
      </Example>
      <Example title="Buttons">
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
      </Example>
      <ModalExample />
      <Example title="Progress Bars">
        <div className="text-center"> (se "0%") </div>
        <Progress />
        <div className="text-center"> (se "25%") </div>
        <Progress value=25.0/>
        <div className="text-center"> (se "50%") </div>
        <Progress value=50.0/>
        <div className="text-center"> (se "100%") </div>
        <Progress value=100.0/>
        <div className="text-center"> (se "Multiple bars") </div>
        <Progress multi=true> 
          <Progress bar=true value=15.0 > (se "15%")</Progress>
          <Progress bar=true value=15.0 color=Progress.BackgroundColor.Success />
          <Progress bar=true value=15.0 color=Progress.BackgroundColor.Info />
          <Progress bar=true value=15.0 color=Progress.BackgroundColor.Warning />
          <Progress bar=true value=15.0 color=Progress.BackgroundColor.Danger />
        </Progress>
        <div className="text-center"> (se "Striped") </div>
        <Progress value=50.0 color=Progress.BackgroundColor.Info striped=true > (se "Striped") </Progress>
        <div className="text-center"> (se "Animated") </div>
        <Progress value=50.0 color=Progress.BackgroundColor.Danger animated=true > (se "Animated") </Progress>
      </Example>
    </Layout.Container>
};