include WidgetPlaying.Bootstrap;

let code: string =
  [%bs.raw {|require('Examples/ButtonExample.re').default|}] |> Examples.prepCode;

let se = React.string;

[@react.component]
let make = () => {
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
