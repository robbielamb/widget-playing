include Utils;



[@react.component]
let make =
    (
      ~inline: bool=false,
      ~onSubmit: option(ReactEvent.Form.t => unit)=?,
      ~className: option(string)=?,
      ~children,
    ) => {

    let className =
      [unwrapStr(i, className), inline ? "form-inline" : ""]
      |> String.concat(" ");    
    <form className ?onSubmit > children </form>
   
  };

module Feedback = {
  let component = ReasonReact.statelessComponent("Form.Feedback");

  let make = (~tag: string="div", ~valid: bool=true, children) => {
    ...component,
    render: _self => {
      let className = valid ? "is-valid" : "is-invalid";
      let props = ReactDOMRe.objToDOMProps({"className": className});
      ReactDOMRe.createElementVariadic(tag, ~props, children);
    },
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
          "valid": option('valid),
          "tag": option('tag),
          "children": 'children,
        },
      ) =>
      make(
        ~valid=?reactProps##valid,
        ~tag=?reactProps##tag,
        reactProps##children,
      )
    );
  [@bs.obj]
  external makeProps:
    (~children: 'children, ~tag: 'tag=?, ~valid: 'valid=?, unit) =>
    {
      .
      "valid": option('valid),
      "tag": option('tag),
      "children": 'children,
    } =
    "";
};

module Group = {
  let component = ReasonReact.statelessComponent("Form.Group");
  let make =
      (
        ~tag: string="div",
        ~row: bool=false,
        ~disabled: bool=false,
        ~className: option(string)=?,
        children,
      ) => {
    ...component,
    render: _self => {
      let classes =
        [
          unwrapStr(i, className),
          "form-group",
          row ? "row" : "",
          disabled ? "disabled" : "",
        ]
        |> String.concat(" ");
      let props = {"className": classes}->ReactDOMRe.objToDOMProps;
      ReactDOMRe.createElementVariadic(tag, ~props, children);
    },
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
          "className": option('className),
          "disabled": option('disabled),
          "row": option('row),
          "tag": option('tag),
          "children": 'children,
        },
      ) =>
      make(
        ~className=?reactProps##className,
        ~disabled=?reactProps##disabled,
        ~row=?reactProps##row,
        ~tag=?reactProps##tag,
        reactProps##children,
      )
    );
  [@bs.obj]
  external makeProps:
    (
      ~children: 'children,
      ~tag: 'tag=?,
      ~row: 'row=?,
      ~disabled: 'disabled=?,
      ~className: 'className=?,
      unit
    ) =>
    {
      .
      "className": option('className),
      "disabled": option('disabled),
      "row": option('row),
      "tag": option('tag),
      "children": 'children,
    } =
    "";
};

module Check = {
  let component = ReasonReact.statelessComponent("Form.Group");
  let make =
      (
        ~tag: string="div",
        ~row: bool=false,
        ~inline: bool=false,
        ~disabled: bool=false,
        ~className: option(string)=?,
        children,
      ) => {
    ...component,
    render: _self => {
      let classes =
        [
          unwrapStr(i, className),
          "form-check",
          row ? "row" : "",
          inline ? "form-check-inline" : "",
          disabled ? "disabled" : "",
        ]
        |> String.concat(" ");
      let props = {"className": classes}->ReactDOMRe.objToDOMProps;
      ReactDOMRe.createElementVariadic(tag, ~props, children);
    },
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
          "className": option('className),
          "disabled": option('disabled),
          "inline": option('inline),
          "row": option('row),
          "tag": option('tag),
          "children": 'children,
        },
      ) =>
      make(
        ~className=?reactProps##className,
        ~disabled=?reactProps##disabled,
        ~inline=?reactProps##inline,
        ~row=?reactProps##row,
        ~tag=?reactProps##tag,
        reactProps##children,
      )
    );
  [@bs.obj]
  external makeProps:
    (
      ~children: 'children,
      ~tag: 'tag=?,
      ~row: 'row=?,
      ~inline: 'inline=?,
      ~disabled: 'disabled=?,
      ~className: 'className=?,
      unit
    ) =>
    {
      .
      "className": option('className),
      "disabled": option('disabled),
      "inline": option('inline),
      "row": option('row),
      "tag": option('tag),
      "children": 'children,
    } =
    "";
};

module Text = {
  let component = ReasonReact.statelessComponent("Form.Text");
  let make =
      (
        ~tag: string="small",
        ~inline: bool=false,
        ~color: ColorsRe.Text.t=ColorsRe.Text.Muted,
        ~className: option(string)=?,
        children,
      ) => {
    ...component,
    render: _self => {
      let classes =
        [
          unwrapStr(i, className),
          !inline ? "form-text" : "",
          ColorsRe.Text.toString(color),
        ]
        |> String.concat(" ");
      let props = {"className": classes}->ReactDOMRe.objToDOMProps;
      ReactDOMRe.createElementVariadic(tag, ~props, children);
    },
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
          "className": option('className),
          "color": option('color),
          "inline": option('inline),
          "tag": option('tag),
          "children": 'children,
        },
      ) =>
      make(
        ~className=?reactProps##className,
        ~color=?reactProps##color,
        ~inline=?reactProps##inline,
        ~tag=?reactProps##tag,
        reactProps##children,
      )
    );
  [@bs.obj]
  external makeProps:
    (
      ~children: 'children,
      ~tag: 'tag=?,
      ~inline: 'inline=?,
      ~color: 'color=?,
      ~className: 'className=?,
      unit
    ) =>
    {
      .
      "className": option('className),
      "color": option('color),
      "inline": option('inline),
      "tag": option('tag),
      "children": 'children,
    } =
    "";
};

/* ~inline: bool=false, */

/* Should this just be a Label? Should we have an Input doo dad with an Input.Label? Then perhaps an Input.Text? */
