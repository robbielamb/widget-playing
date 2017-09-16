include Utils;

include Colors;

let component = ReasonReact.statelessComponent "Form";

let make
    tag::(tag: string)="form"
    inline::(inline: bool)=false
    className::(className: option string)=?
    children => {
  let classes = [unwrapStr i className, inline ? "form-inline" : ""] |> String.concat " ";
  ReasonReact.createDomElement tag props::{"className": classes} children
};

module Feedback = {};

module Group = {
  /* TODO: Finish form-group and form-check */
  let component = ReasonReact.statelessComponent "Form.Group";
  let make
      tag::(tag: string)="div"
      row::(row: bool)=false
      check::(check: bool)=false
      disabled::(disabled: bool)=false
      inline::(inline: bool)=false
      className::(className: option string)=?
      children => {
    let classes =
      [
        unwrapStr i className,
        row ? "row" : "",
        check ? "form-check" : "form-group",
        check && disabled ? "disabled" : "",
        check && inline ? "form-check-inline" : ""
      ] |>
      String.concat " ";
    ReasonReact.createDomElement tag props::{"className": classes} children
  };
};

module Text = {
  let component = ReasonReact.statelessComponent "Form.Text";
  let make
      tag::(tag: string)="small"
      inline::(inline: bool)=false
      color::(color: option TextColor.t)=?
      className::(className: option string)=?
      children => {
    let classes =
      [unwrapStr i className, not inline ? "form-text" : "", TextColor.unWrap color] |>
      String.concat " ";
    ReasonReact.createDomElement tag props::{"className": classes} children
  };
};