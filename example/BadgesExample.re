include WidgetPlaying.Bootstrap;

let code: string =
  [%bs.raw {|require('Examples/BadgesExample.re')|}] |> Examples.prepCode;

let se = React.string;

let component = ReasonReact.statelessComponent("BadgesExample");

let make = _children => {
  ...component,
  render: _self =>
    <Examples.Example title="Badges">
      <Badge color=Colors.Color.Primary> (se("Default")) </Badge>
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
