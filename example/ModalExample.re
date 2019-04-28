include WidgetPlaying.Bootstrap;

let code: string =
  [%bs.raw {|require('Examples/ModalExample.re').default|}] |> Examples.prepCode;

let se = React.string;

/* type action =
  | Toggle;

type state = bool;

let toggle = event => {
  Js.log2("Toggling modal", event);
  Toggle;
};
*/

[@react.component]
let make = () => {
  
    let (isOpen, setOpen) = React.useState(() => false);

    let toggleModal = (_event) => {
      setOpen((isOpen) => !isOpen)
    };

    <Examples.Example title="Modal">
      <Button color=Button.Color.Danger onClick=(toggleModal)>
        (se("Launch Modal"))
      </Button>
      <Modal isOpen>
        <Modal.Header toggle=(toggleModal)>
          (se("Modal Header"))
        </Modal.Header>
        <Modal.Body>
          (se("This is the modal body where I can put stuff"))
        </Modal.Body>
        <Modal.Footer>
          <Button color=Button.Color.Primary onClick=(toggleModal)>
            (se("Do Something"))
          </Button>
          <Button
            color=Button.Color.Secondary onClick=(toggleModal)>
            (se("Cancel"))
          </Button>
        </Modal.Footer>
      </Modal>
      (Examples.exampleHighlight(code))
    </Examples.Example>
};

