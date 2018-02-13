include WidgetPlaying.Bootstrap;

let code: string =
  [%bs.raw {|require('Examples/AlertExample.re')|}] |> Examples.prepCode;

let se = ReasonReact.stringToElement;

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
          (ReasonReact.stringToElement("Success"))
        </Alert.Heading>
        <p> (ReasonReact.stringToElement(message)) </p>
      </Alert.Auto>
      (Examples.highlight(code))
    </Examples.Example>
};