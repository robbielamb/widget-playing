include Utils;

module Size = {
  type t =
    | None
    | Large
    | Small;
  let toString = size =>
    switch (size) {
    | None => ""
    | Large => "form-control-lg"
    | Small => "form-control-sm"
    };
};

type inputType =
  | Button
  | Checkbox
  | Date
  | Email
  | File
  | Password
  | Radio
  | Reset
  //| Select
  | Submit
  | Text
  | TextArea
  | Url;

[@react.component]
let make =
    (
      ~id: option(string)=?,
      ~name: string="",
      ~type_: inputType=Text,
      ~size: Size.t=Size.None,
      ~plainText: bool=false,
      ~placeholder: option(string)=?,
      ~disabled: bool=false,
      ~className: option(string)=?,
      ~onInput: option(ReactEvent.Form.t => unit)=?,
      ~onChange: option(ReactEvent.Form.t => unit)=?,
      ~onBlur: option(ReactEvent.Focus.t => unit)=?,
      ~checked: option(bool)=?,
      ~valid: option(bool)=?,
      ~value: option(string)=?,
      ~required: bool=false,
    ) => {
  let checkInput =
    switch (type_) {
    | Radio => true
    | Checkbox => true
    | _ => false
    };
  let fileInput = type_ === File;

  let typeAttribute =
    switch (type_) {
    | Button => "button"
    | Checkbox => "checkbox"
    | Date => "date"
    | Email => "email"
    | File => "file"
    | Password => "password"
    | Radio => "radio"
    | Reset => "reset"
    //| Select => ""
    | Submit => "submit"
    | TextArea => ""
    | Text => "text"
    | Url => "url"
    };
  let formControlClass =
    switch (plainText, fileInput, checkInput) {
    | (true, false, false) => "form-control-planetext"
    | (false, true, false) => "form-control-file"
    | (false, false, true) => "form-check-input"
    | (_, _, _) => "form-control"
    };
  let validClassName =
    switch (valid) {
    | None => ""
    | Some(true) => "is-valid"
    | Some(false) => "is-invalid"
    };
  let className =
    [
      unwrapStr(i, className),
      Size.toString(size),
      formControlClass,
      validClassName,
    ]
    |> String.concat(" ");

  switch (type_) {
  | TextArea =>
    <textarea
      className
      ?id
      name
      type_=typeAttribute
      disabled
      ?placeholder
      ?onInput
      ?onChange
      ?onBlur
      ?checked
      ?value
      required
    />
  | _ =>
    <input
      className
      ?id
      name
      type_=typeAttribute
      disabled
      ?placeholder
      ?onInput
      ?onChange
      ?onBlur
      ?checked
      ?value
      required
    />
  };
  /* let props =
       {
         "className": className,
         "id": Js.Nullable.fromOption(id),
         "name": name,
         "type": typeAttribute,
         "placeholder": Js.Nullable.fromOption(placeholder),
         "multiple": Js.Nullable.fromOption(multiple),
         "disabled": disabled,
         "onInput": Js.Nullable.fromOption(onInput),
         "onChange": Js.Nullable.fromOption(onChange),
         "onBlur": Js.Nullable.fromOption(onBlur),
         "checked": Js.Nullable.fromOption(checked),
         "value": Js.Nullable.fromOption(value),
         "required": required,
       }
       ->ReactDOMRe.objToDOMProps;
     ReactDOMRe.createElementVariadic(tag, ~props, children); */
};

module Select = {
  [@react.component]
  let make =
      (
        ~id: option(string)=?,
        ~name: string="",
        ~size: Size.t=Size.None,
        ~multiple=false,
        ~className: option(string)=?,
        ~disabled=false,
        ~placeholder: option(string)=?,
        ~onInput: option(ReactEvent.Form.t => unit)=?,
        ~onChange: option(ReactEvent.Form.t => unit)=?,
        ~onBlur: option(ReactEvent.Focus.t => unit)=?,
        ~children,
      ) => {
    let className =
      [unwrapStr(i, className), Size.toString(size), "form-control"]
      |> String.concat(" ");
    <select
      ?id
      name
      className
      multiple
      disabled
      ?placeholder
      ?onInput
      ?onChange
      ?onBlur>
      children
    </select>;
  };
};

module Label = {
  include LayoutRe.ColSizes;
  module Size = {
    type t =
      | SM
      | LG;
    let toString = size =>
      switch (size) {
      | SM => "sm"
      | LG => "lg"
      };
  };

  [@react.component]
  let make =
      (
        ~id: option(string)=?,
        ~htmlFor: option(string)=?,
        ~hidden: bool=false,
        ~check: bool=false,
        ~inline: bool=false,
        ~disabled: bool=false,
        ~size: option(Size.t)=?,
        ~color: option(ColorsRe.Text.t)=?,
        ~xs: option(shape)=?,
        ~sm: option(shape)=?,
        ~md: option(shape)=?,
        ~lg: option(shape)=?,
        ~xl: option(shape)=?,
        ~className: option(string)=?,
        ~children,
      ) => {
    let colClasses = processShapeList(xs, sm, md, lg, xl);
    let containsColClasses = Belt.List.length(colClasses) > 0;
    let className =
      [
        unwrapStr(i, className),
        hidden ? "sr-only" : "",
        check && !inline ? "form-check-label" : "",
        check && inline ? "form-check-inline" : "",
        check && inline && disabled ? "disabled" : "",
        switch (size) {
        | None => ""
        | Some(s) => "col-form-label-" ++ Size.toString(s)
        },
        containsColClasses ? "col-form-label" : "",
        !check && !containsColClasses ? "form-control-label" : "",
        ColorsRe.Text.unWrap(color),
      ]
      ->(Belt.List.concat(colClasses))
      |> String.concat(" ");
    <label className ?id ?htmlFor> children </label>;
  };
};