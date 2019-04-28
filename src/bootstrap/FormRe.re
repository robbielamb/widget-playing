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
  <form className ?onSubmit> children </form>;
};

module Feedback = {
  let make = (~valid: bool=true, ~children) => {
    let className = valid ? "is-valid" : "is-invalid";
    <div className> children </div>;
  };
};

module Group = {
  [@react.component]
  let make =
      (
        ~row: bool=false,
        ~disabled: bool=false,
        ~className: option(string)=?,
        ~children,
      ) => {
    let className =
      [
        unwrapStr(i, className),
        "form-group",
        row ? "row" : "",
        disabled ? "disabled" : "",
      ]
      |> String.concat(" ");
    <div className> children </div>;
  };
};

module Fieldset = {
  [@react.component]
  let make =
      (
        ~row: bool=false,
        ~disabled: bool=false,
        ~className: option(string)=?,
        ~children,
      ) => {
    let className =
      [
        unwrapStr(i, className),
        "form-group",
        row ? "row" : "",
        disabled ? "disabled" : "",
      ]
      |> String.concat(" ");
    <fieldset className> children </fieldset>;
  };
};

module Check = {
  [@react.component]
  let make =
      (
        ~row: bool=false,
        ~inline: bool=false,
        ~disabled: bool=false,
        ~className: option(string)=?,
        ~children,
      ) => {
    let className =
      [
        unwrapStr(i, className),
        "form-check",
        row ? "row" : "",
        inline ? "form-check-inline" : "",
        disabled ? "disabled" : "",
      ]
      |> String.concat(" ");
    <div className> children </div>;
  };
};

module Text = {
  [@react.component]
  let make =
      (
        ~inline: bool=false,
        ~color: ColorsRe.Text.t=ColorsRe.Text.Muted,
        ~className: option(string)=?,
        ~children,
      ) => {
    let className =
      [
        unwrapStr(i, className),
        !inline ? "form-text" : "",
        ColorsRe.Text.toString(color),
      ]
      |> String.concat(" ");
    <small className> children </small>;
  };
};

/* ~inline: bool=false, */

/* Should this just be a Label? Should we have an Input doo dad with an Input.Label? Then perhaps an Input.Text? */