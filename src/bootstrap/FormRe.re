include Utils;

let component = ReasonReact.statelessComponent("Form");

let make =
    (
      ~tag: string="form",
      ~inline: bool=false,
      ~onSubmit: option(ReactEvent.Form.t => unit)=?,
      ~className: option(string)=?,
      children,
    ) => {
  ...component,
  render: _self => {
    let classes = [unwrapStr(i, className), inline ? "form-inline" : ""] |> String.concat(" ");
    let props = ReactDOMRe.objToDOMProps({"className": classes, "onSubmit": Js.Nullable.fromOption(onSubmit)});

    ReactDOMRe.createElementVariadic(tag, ~props, children);
  },
};

module Feedback = {
  let component = ReasonReact.statelessComponent("Form.Feedback");

  let make = (~tag: string="div", ~valid: bool=true, children) => {
    ...component,
    render: _self => {
      let className = valid ? "is-valid" : "is-invalid";
      let props=ReactDOMRe.objToDOMProps({"className": className});
      ReactDOMRe.createElementVariadic(tag, ~props, children);
    },
  };
};

module Group = {
  let component = ReasonReact.statelessComponent("Form.Group");
  let make =
      (
        ~tag: string="div",
        ~row: bool=false,
        ~disabled: bool=false,
        /* ~inline: bool=false, */
        ~className: option(string)=?,
        children,
      ) => {
    ...component,
    render: _self => {
      let classes =
        [unwrapStr(i, className), "form-group", row ? "row" : "", disabled ? "disabled" : ""] |> String.concat(" ");
        let props = {"className": classes} |. ReactDOMRe.objToDOMProps;
      ReactDOMRe.createElementVariadic(tag, ~props, children);
    },
  };
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
      let props = {"className": classes} |. ReactDOMRe.objToDOMProps;
      ReactDOMRe.createElementVariadic(tag, ~props, children);
    },
  };
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
        [unwrapStr(i, className), ! inline ? "form-text" : "", ColorsRe.Text.toString(color)] |> String.concat(" ");
        let props={"className": classes} |. ReactDOMRe.objToDOMProps;
      ReactDOMRe.createElementVariadic(tag, ~props, children);
    },
  };
};
/* Should this just be a Label? Should we have an Input doo dad with an Input.Label? Then perhaps an Input.Text? */