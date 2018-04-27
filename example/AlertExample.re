include WidgetPlaying.Bootstrap;

let code: string =
  [%bs.raw {|require('Examples/AlertExample.re')|}] |> Examples.prepCode;

let se = ReasonReact.string;

type action =
  | Toggle;

type state = bool;

let toggle = (event: ReactEventRe.Mouse.t) => {
  Js.log(event);
  Toggle;
};

let component = ReasonReact.statelessComponent("AlertExample");

let make = (~message, _children) => {
  ...component,
  render: _self =>
    <Examples.Example title="Alerts">
      <Alert.Auto color=Colors.Color.Warning>
        <Alert.Heading>
          (ReasonReact.string("Success"))
        </Alert.Heading>
        <p> (ReasonReact.string(message)) </p>
      </Alert.Auto>
      (Examples.highlight(code))
    </Examples.Example>
};