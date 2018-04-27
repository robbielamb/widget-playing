include WidgetPlaying.Bootstrap;

let code: string =
  [%bs.raw {|require('Examples/FormsExample.re')|}] |> Examples.prepCode;

let se = ReasonReact.string;

let component = ReasonReact.statelessComponent("FormExample");

let make = _children => {
  ...component,
  render: _self =>
    <Examples.Example title="Forms & Input">
      <Form>
        <Form.Group>
          <Input.Label _for="exampleEmail"> (se("Email")) </Input.Label>
          <Input
            _type=Input.Email
            name="email"
            id="exampleEmail"
            placeholder="with a placeholder"
          />
        </Form.Group>
        <Form.Group>
          <Input.Label _for="examplePassword"> (se("Password")) </Input.Label>
          <Input
            _type=Input.Password
            name="email"
            id="examplePassword"
            placeholder="password here"
          />
        </Form.Group>
        <Form.Group>
          <Input.Label _for="selectExample"> (se("Select")) </Input.Label>
          <Input
            _type=Input.Select
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
          <Input.Label _for="selecMultitExample">
            (se("Select Multiple"))
          </Input.Label>
          <Input
            _type=Input.Select
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
          <Input.Label _for="exampleTextArea"> (se("Text Area")) </Input.Label>
          <Input
            _type=Input.TextArea
            name="textarea"
            id="exampleTextArea"
            placeholder="with a placeholder"
          />
        </Form.Group>
        <Form.Group>
          <Input.Label _for="exampleFile">
            (se("File Upload Time"))
          </Input.Label>
          <Input
            _type=Input.File
            name="file"
            id="exampleFile"
            placeholder="with a placeholder"
          />
          <Form.Text>
            (
              se(
                "This is a bit of example text to help explain the dialog above."
              )
            )
          </Form.Text>
        </Form.Group>
        <Form.Group tag="fieldset">
          <legend> (se("Hello Radio (buttons>")) </legend>
          <Form.Check>
            <Input.Label check=true>
              <Input _type=Input.Radio name="radio1" />
              (se(" Radio 1"))
            </Input.Label>
          </Form.Check>
          <Form.Check>
            <Input.Label check=true>
              <Input _type=Input.Radio name="radio1" />
              (se(" Radio 2"))
            </Input.Label>
          </Form.Check>
          <Form.Check disabled=true>
            <Input.Label check=true>
              <Input _type=Input.Radio name="radio1" disabled=true />
              (se(" Radio 3 - Disabled"))
            </Input.Label>
          </Form.Check>
        </Form.Group>
        <Form.Check>
          <Input.Label check=true>
            <Input _type=Input.Checkbox name="check-box" />
            (se("  This is a checkbox"))
          </Input.Label>
        </Form.Check>
      </Form>
      (Examples.exampleHighlight(code))
    </Examples.Example>
};