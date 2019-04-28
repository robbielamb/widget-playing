include WidgetPlaying.Bootstrap;

let code: string =
  [%bs.raw {|require('Examples/AlertExample.re').default|}]
  |> Examples.prepCode;

let se = React.string;

type action =
  | Toggle;

type state = bool;

let toggle = (event: ReactEvent.Mouse.t) => {
  Js.log(event);
  Toggle;
};

[@react.component]
let make = (~message) => {
  <Examples.Example title="Alerts">
    <Alert.Auto color=Colors.Color.Warning>
      <Alert.Heading> {React.string("Success")} </Alert.Heading>
      <p> {React.string(message)} </p>
    </Alert.Auto>
    {Examples.highlight(code)}
  </Examples.Example>;
};