include WidgetPlaying.Bootstrap;

let code: string =
  [%bs.raw {|require('Examples/ModalExample.re')|}] |> Examples.prepCode;

let se = ReasonReact.stringToElement;

type action =
  | Toggle;

type state = bool;

let toggle = event => {
  Js.log2("Toggling modal", event);
  Toggle;
};

let component = ReasonReact.reducerComponent("ButtonExample");

let make = _children => {
  ...component,
  initialState: () => false,
  reducer: (action, state) =>
    switch action {
    | Toggle => ReasonReact.Update(! state)
    },
  render: ({state, send}) =>
    <Examples.Example title="Modal">
      <Button color=Button.Color.Danger onClick=(_event => send(Toggle))>
        (se("Launch Modal"))
      </Button>
      <Modal isOpen=state>
        <Modal.Header toggle=(_event => send(Toggle))>
          (se("Modal Header"))
        </Modal.Header>
        <Modal.Body>
          (se("This is the modal body where I can put stuff"))
        </Modal.Body>
        <Modal.Footer>
          <Button color=Button.Color.Primary onClick=(_event => send(Toggle))>
            (se("Do Something"))
          </Button>
          <Button
            color=Button.Color.Secondary onClick=(_event => send(Toggle))>
            (se("Cancel"))
          </Button>
        </Modal.Footer>
      </Modal>
      (Examples.exampleHighlight(code))
    </Examples.Example>
};