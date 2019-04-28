include WidgetPlaying.Bootstrap;

let code: string =
  [%bs.raw {|require('Examples/BadgesExample.re').default|}] |> Examples.prepCode;

let se = React.string;

[@react.component]
let make = () => {
 
    <Examples.Example title="Badges">
      <Badge color=Colors.Color.Primary> (se("Default")) </Badge>
      (Examples.exampleHighlight(code))
    </Examples.Example>
};
