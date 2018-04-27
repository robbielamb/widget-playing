include WidgetPlaying.Bootstrap;

let code: string =
  [%bs.raw {|require('Examples/ButtonExample.re')|}] |> Examples.prepCode;

let se = ReasonReact.string;

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
    </Examples.Example>
};