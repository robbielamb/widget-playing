include WidgetPlaying.Bootstrap;

let code: string =
  [%bs.raw {|require('Examples/FormsExample.re')|}] |> Examples.prepCode;

let se = React.string;

let component = ReasonReact.statelessComponent("FormExample");

let make = _children => {
  ...component,
  render: _self =>
    <Examples.Example title="Forms & Input">
      <Form>
        <Form.Group>
          <Input.Label for_="exampleEmail"> (se("Email")) </Input.Label>
          <Input
            type_=Input.Email
            name="email"
            id="exampleEmail"
            placeholder="with a placeholder"
          />
        </Form.Group>
        <Form.Group>
          <Input.Label for_="examplePassword"> (se("Password")) </Input.Label>
          <Input
            type_=Input.Password
            name="password"
            id="examplePassword"
            placeholder="password here"
          />
        </Form.Group>
        <Form.Group>
          <Input.Label for_="exampleRequired">
            (se("Required Field"))
          </Input.Label>
          <Input
            type_=Input.Text
            name="required"
            id="exampleRequired"
            placeholder="Required Text"
            required=true
          />
        </Form.Group>
        <Form.Group>
          <Input.Label for_="exampleDate"> (se("Date")) </Input.Label>
          <Input
            type_=Input.Date
            name="exampleDate"
            id="exampleDate"
            placeholder="Birthday!"
            required=true
          />
        </Form.Group>
        <Form.Group>
          <Input.Label for_="selectExample"> (se("Select")) </Input.Label>
          <Input
            type_=Input.Select
            name="select"
            id="selectExample"
            placeholder="foo">
            <option> (se("1")) </option>
            <option> (se("2")) </option>
            <option> (se("3")) </option>
            <option> (se("4")) </option>
          </Input>
        </Form.Group>
        <Form.Group>
          <Input.Label for_="selecMultitExample">
            (se("Select Multiple"))
          </Input.Label>
          <Input
            type_=Input.Select
            name="multi-select"
            id="selectMultiExample"
            placeholder="foo"
            multiple=true>
            <option> (se("1")) </option>
            <option> (se("2")) </option>
            <option> (se("3")) </option>
            <option> (se("4")) </option>
            <option> (se("5")) </option>
            <option> (se("6")) </option>
          </Input>
        </Form.Group>
        <Form.Group>
          <Input.Label for_="exampleTextArea">
            (se("Text Area"))
          </Input.Label>
          <Input
            type_=Input.TextArea
            name="textarea"
            id="exampleTextArea"
            placeholder="with a placeholder"
          />
        </Form.Group>
        <Form.Group>
          <Input.Label for_="exampleFile">
            (se("File Upload Time"))
          </Input.Label>
          <Input
            type_=Input.File
            name="file"
            id="exampleFile"
            placeholder="with a placeholder"
          />
          <Form.Text>
            (
              se(
                "This is a bit of example text to help explain the dialog above.",
              )
            )
          </Form.Text>
        </Form.Group>
        <Form.Group tag="fieldset">
          <legend> (se("Hello Radio (buttons>")) </legend>
          <Form.Check>
            <Input.Label check=true>
              <Input type_=Input.Radio name="radio1" />
              (se(" Radio 1"))
            </Input.Label>
          </Form.Check>
          <Form.Check>
            <Input.Label check=true>
              <Input type_=Input.Radio name="radio1" />
              (se(" Radio 2"))
            </Input.Label>
          </Form.Check>
          <Form.Check disabled=true>
            <Input.Label check=true>
              <Input type_=Input.Radio name="radio1" disabled=true />
              (se(" Radio 3 - Disabled"))
            </Input.Label>
          </Form.Check>
        </Form.Group>
        <Form.Check>
          <Input.Label check=true>
            <Input type_=Input.Checkbox name="check-box" />
            (se("  This is a checkbox"))
          </Input.Label>
        </Form.Check>
      </Form>
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
