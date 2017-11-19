include Utils;

let component = ReasonReact.statelessComponent("Form");

let make = (~tag: string="form", ~inline: bool=false, ~className: option(string)=?, children) => {
  ...component,
  render: (_self) => {
    let classes = [unwrapStr(i, className), inline ? "form-inline" : ""] |> String.concat(" ");
    ReasonReact.createDomElement(tag, ~props={"className": classes}, children)
  }
};

module Feedback = {};

module Group = {
  let component = ReasonReact.statelessComponent("Form.Group");
  let make =
      (
        ~tag: string="div",
        ~row: bool=false,
        ~disabled: bool=false,
        ~inline: bool=false,
        ~className: option(string)=?,
        children
      ) => {
    ...component,
    render: (_self) => {
      let classes =
        [unwrapStr(i, className), "form-group", row ? "row" : "", disabled ? "disabled" : ""]
        |> String.concat(" ");
      ReasonReact.createDomElement(tag, ~props={"className": classes}, children)
    }
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
        children
      ) => {
    ...component,
    render: (_self) => {
      let classes =
        [
          unwrapStr(i, className),
          "form-check",
          row ? "row" : "",
          inline ? "form-check-inline" : "",
          disabled ? "disabled" : ""
        ]
        |> String.concat(" ");
      ReasonReact.createDomElement(tag, ~props={"className": classes}, children)
    }
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
        children
      ) => {
    ...component,
    render: (_self) => {
      let classes =
        [unwrapStr(i, className), ! inline ? "form-text" : "", ColorsRe.Text.toString(color)]
        |> String.concat(" ");
      ReasonReact.createDomElement(tag, ~props={"className": classes}, children)
    }
  };
};
/* Should this just be a Label? Should we have an Input doo dad with an Input.Label? Then perhaps an Input.Text? */