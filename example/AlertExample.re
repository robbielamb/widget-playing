include WidgetPlaying.Bootstrap;

let code: string =
  [%bs.raw {|require('Examples/AlertExample.re')|}] |> Examples.prepCode;

let se = React.string;

type action =
  | Toggle;

type state = bool;

let toggle = (event: ReactEvent.Mouse.t) => {
  Js.log(event);
  Toggle;
};

let component = ReasonReact.statelessComponent("AlertExample");

let make = (~message, _children) => {
  ...component,
  render: _self =>
    <Examples.Example title="Alerts">
      <Alert.Auto color=Colors.Color.Warning>
        <Alert.Heading> (React.string("Success")) </Alert.Heading>
        <p> (React.string(message)) </p>
      </Alert.Auto>
      (Examples.highlight(code))
    </Examples.Example>,
};
/**
 * This is a wrapper created to let this component be used from the new React api.
 * Please convert this component to a [@react.component] function and then remove this wrapping code.
 */
let make =
  ReasonReactCompat.wrapReasonReactForReact(
    ~component,
    (
      reactProps: {
        .
        "message": 'message,
        "children": 'children,
      },
    ) =>
    make(~message=reactProps##message, reactProps##children)
  );
[@bs.obj]
external makeProps:
  (~children: 'children, ~message: 'message, unit) =>
  {
    .
    "message": 'message,
    "children": 'children,
  } =
  "";
