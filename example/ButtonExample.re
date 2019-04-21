include WidgetPlaying.Bootstrap;

let code: string =
  [%bs.raw {|require('Examples/ButtonExample.re')|}] |> Examples.prepCode;

let se = React.string;

let component = ReasonReact.statelessComponent("ButtonExample");

let make = _children => {
  ...component,
  render: _self =>
    <Examples.Example title="Buttons">
      <Button color=Button.Color.Primary size=Button.Size.LG>
        (se("Primary"))
      </Button>
      (se(" "))
      <Button color=Button.Color.Secondary> (se("Secondary")) </Button>
      (se(" "))
      <Button color=Button.Color.Success> (se("Success")) </Button>
      (se(" "))
      <Button color=Button.Color.Info> (se("Info")) </Button>
      (se(" "))
      <Button color=Button.Color.Warning> (se("Warning")) </Button>
      (se(" "))
      <Button color=Button.Color.Danger> (se("Danger")) </Button>
      (se(" "))
      <Button color=Button.Color.Link> (se("Link")) </Button>
      (Examples.exampleHighlight(code))
    </Examples.Example>,
};
/**
 * This is a wrapper created to let this component be used from the new React api.
 * Please convert this component to a [@react.component] function and then remove this wrapping code.
 */
let make =
  ReasonReactCompat.wrapReasonReactForReact(
    ~component, (reactProps: {. "children": 'children}) =>
    make(reactProps##children)
  );
[@bs.obj]
external makeProps: (~children: 'children, unit) => {. "children": 'children} =
  "";
